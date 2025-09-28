/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:05:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/28 16:34:00 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

typedef struct s_exec
{
	int		pid;
	int		pipe[2][2];
	int		redir_in;
	int		redir_out;
	int		status;
	size_t	curr;
	size_t	cmd_count;
}	t_exec;

void	init_exec(t_data *data, t_exec *exec)
{
	t_cmd	*ptr;

	ft_bzero(exec, sizeof(t_exec));
	ft_memset(&exec->pid, -1, sizeof(int));	
	ft_memset(&exec->pipe, -1, 4 * sizeof(int));
	ptr = data->cmd;
	while (ptr)
	{
		exec->cmd_count++;
		ptr = ptr->next;
	}
}

int isbuiltin(char *s)
{
	if (s == NULL)
		return (0);
	if (
		   !ft_strcmp("echo", s)
		|| !ft_strcmp("cd", s)
		|| !ft_strcmp("pwd", s)
		|| !ft_strcmp("export", s)
		|| !ft_strcmp("unset", s)
		|| !ft_strcmp("env", s)
		|| !ft_strcmp("exit", s)
	)
		return (1);
	else
		return (0);
}

// {
// 		if (exec.cmd_count == 1 && !data->cmd->cmd)
// 	{
// 		t_redir *ptr;
// 		exec.redir_in = -1;
// 		exec.redir_out = -1;
// 		ptr = data->cmd->redirs;
// 		while (ptr)
// 		{
// 			if (ptr->type == R_IN)
// 			{
// 				if (exec.redir_in != -1)
// 					close(exec.redir_in);
// 				exec.redir_in = open(ptr->filename, O_RDONLY);
// 				if (exec.redir_in == -1)
// 				{
// 					perror(ptr->filename);
// 					data->ret = -1; //change
// 					return (0);
// 				}
// 			}
// 			else if (ptr->type == R_OUT)
// 			{
// 				if (exec.redir_out != -1)
// 					close(exec.redir_out);
// 				exec.redir_out = open(ptr->filename, O_RDONLY | O_CREAT | O_TRUNC, 0600);
// 				if (exec.redir_out == -1)
// 				{
// 					perror(ptr->filename);
// 					data->ret = -1; //change
// 					return (0);
// 				}
// 			}
// 			else if (ptr->type == R_APPEND)
// 			{
// 				if (exec.redir_out != -1)
// 					close(exec.redir_out);
// 				exec.redir_out = open(ptr->filename, O_RDONLY | O_CREAT | O_APPEND, 0600);
// 				if (exec.redir_out == -1)
// 				{
// 					perror(ptr->filename);
// 					data->ret = -1; //change
// 					return (0);
// 				}
// 			}
// 			ptr = ptr->next;	
// 		}
// 	}
// }

int	single_builtin()
{
	printf("todo\n");
	return (0);
}

void executer_child_open(t_data *data, t_cmd *cmd, t_exec *exec)
{
	t_redir *ptr;

	ptr = cmd->redirs;
	while (ptr)
	{
		if (ptr->type == R_IN && exec->redir_in != -1)
			close(exec->redir_in);
		else if (ptr->type == R_OUT && exec->redir_in != -1)
			close(exec->redir_out);
		if (ptr->type == R_IN)
			exec->redir_in = open(ptr->filename, O_RDONLY);
		else if (ptr->type == R_OUT)
			exec->redir_out = open(ptr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		else if (ptr->type == R_APPEND)
			exec->redir_out = open(ptr->filename, O_WRONLY | O_CREAT | O_APPEND, 0600);
		if ((ptr->type == R_IN && exec->redir_in == -1)
			|| ((ptr->type == R_OUT || ptr->type == R_APPEND) && exec->redir_out == -1))
			ft_exit(data, "open");
		ptr = ptr->next;
	}
}

void	executer_child_pipes(t_data *data, t_cmd *cmd, t_exec *exec)
{
	int ret;

	ret = 0;
	close(exec->pipe[1][1]);
	if ((exec->curr && dup2(exec->pipe[0][1], STDIN_FILENO) == -1)
		|| (cmd->next && dup2(exec->pipe[1][0], STDOUT_FILENO) == -1)
		|| (exec->redir_in != -1 && dup2(exec->pipe[0][1], STDIN_FILENO == -1))
		|| (exec->redir_out != -1 && dup2(exec->pipe[1][0], STDOUT_FILENO) == -1))
		ret = 1;
	close(exec->pipe[0][1]);
	close(exec->pipe[1][0]);
	close(exec->redir_in);
	close(exec->redir_out);
	if (ret)
		ft_exit(data, "dup2");
}

void	get_exec_path(char **s)
{
	char *cmd;

	cmd = *s;
	
}

int executer_child(t_data *data, t_cmd *cmd, t_exec *exec)
{
	sig_execute_child();
	executer_child_open(data, cmd, exec);
	executer_child_pipes(data, cmd, exec);
	get_exec_path(&cmd->args[0]);
	return (0);
}

int executer_parent(t_data *data, t_cmd *cmd, t_exec *exec)
{
	close(exec->pipe[0][1]);
	close(exec->pipe[1][0]);
	(void)cmd;
	(void)data;
	exec->pipe[0][1] = exec->pipe[1][1];
	return (0);
}


int	executer_fork(t_data *data, t_exec *exec)
{
	t_cmd	*ptr;

	ptr = data->cmd;
	sig_execute_parent();
	while(ptr)
	{
		exec->pid = fork();
		if (exec->pid == -1)
			ft_exit(data, "fork");
		else if (!exec->pid)
			executer_child(data, ptr, exec);
		else
			executer_parent(data, ptr, exec);
		ptr = ptr->next;
	}
	while (waitpid(-1, &exec->status, 0))
		;
	if (WIFEXITED(exec->status))
		data->ret = WEXITSTATUS(exec->status);
	else if (WIFSIGNALED(exec->status))
		g_signal = WTERMSIG(exec->status);
	return (0);
}

int executer(t_data *data)
{
	t_exec exec;

	init_exec(data, &exec);

	if (exec.cmd_count == 1 && isbuiltin(data->cmd->cmd))
		single_builtin();
	else
		executer_fork(data, &exec);
	return (1);
}
