/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:57:36 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 15:36:24 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_exec *exec)
{
	if (exec->redir_in != -1)
		close(exec->redir_in);
	if (exec->redir_out != -1)
		close(exec->redir_out);
	if (exec->pipe[0][0] != -1)
		close(exec->pipe[0][0]);
	if (exec->pipe[0][1] != -1)
		close(exec->pipe[0][1]);
	if (exec->pipe[1][0] != -1)
		close(exec->pipe[1][0]);
	if (exec->pipe[1][1] != -1)
		close(exec->pipe[1][1]);
}

int	dup_child(t_exec *exec, size_t c)
{
	int	flag;

	flag = 1;
	if (exec->redir_in != -1)
	{
		if (dup2(exec->redir_in, STDIN_FILENO) == -1)
			flag = 0;
	}
	else if (c > 0)
	{
		if (dup2(exec->pipe[(c + 1) % 2][0], STDIN_FILENO) == -1)
			flag = 0;
	}
	if (exec->redir_out != -1)
	{
		if (dup2(exec->redir_out, STDOUT_FILENO) == -1)
			flag = 0;
	}
	else if (c < exec->cmd_count - 1)
	{
		if (dup2(exec->pipe[c % 2][1], STDOUT_FILENO) == -1)
			flag = 0;
	}
	close_fds(exec);
	return (flag);
}

int	pipeline_child(t_data *data, t_cmd *cmd, t_exec *exec)
{
	char	*buf;

	if (cmd->args && cmd->args[0] && !ft_strchr(cmd->args[0], '/')
		&& ms_getenv(data->env, "PATH"))
	{
		buf = get_path(data, cmd);
		if (!buf)
			ft_exit(data, "malloc");
		free(cmd->args[0]);
		cmd->args[0] = buf;
	}
	sig_execute_child();
	if (!open_files(cmd->redirs, exec))
		return (free_all(data), exit(1), 1);
	if (!dup_child(exec, exec->curr))
		return (free_all(data), exit(1), 1);
	if (!cmd->args || !cmd->args[0])
		return (free_all(data), exit(0), 1);
	execve(cmd->args[0], cmd->args, data->env);
	perror(cmd->cmd);
	if (access(cmd->args[0], F_OK))
		return (free_all(data), exit(127), 1);
	else if (access(cmd->args[0], F_OK | X_OK))
		return (free_all(data), exit(126), 1);
	return (0);
}

static void	close_pipes(int curr, int fd[2])
{
	if (curr > 0)
	{
		if (fd[0] > 1)
			close(fd[0]);
		if (fd[1] > 1)
			close(fd[1]);
	}
}

void	pipeline(t_data *data, t_cmd *cmd, t_exec *exec)
{
	t_cmd	*ptr;

	ptr = cmd;
	while (ptr)
	{
		if (pipe(exec->pipe[exec->curr % 2]))
			ft_exit(data, "pipe");
		exec->redir_in = -1;
		exec->redir_out = -1;
		exec->pid = fork();
		if (exec->pid == -1)
			ft_exit(data, "fork");
		else if (!exec->pid)
			pipeline_child(data, ptr, exec);
		else
			close_pipes(exec->cmd_count, exec->pipe[(exec->curr + 1) % 2]);
		ptr = ptr->next;
		exec->curr++;
	}
	if (exec->pipe[exec->curr % 2][0] > 1)
		close(exec->pipe[exec->curr % 2][0]);
	if (exec->pipe[exec->curr % 2][1] > 1)
		close(exec->pipe[exec->curr % 2][1]);
}
