/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:05:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 20:06:54 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	waiting(t_data *data, t_exec *exec)
{
	t_cmd	*ptr;
	int		*ret;

	ret = &data->ret;
	ptr = data->cmd;
	while (ptr)
	{
		waitpid(-1, &exec->status, 0);
		if (WIFEXITED(exec->status))
			data->ret = WEXITSTATUS(exec->status);
		else if (WIFSIGNALED(exec->status))
		{
			printf("TERMINATED BY SIGNAL: %d\n", WTERMSIG(exec->status));
			*ret = 128 + WTERMSIG(exec->status);
		}
		ptr = ptr->next;
	}
}

int	buffer_fds(int *buffer)
{
	buffer[0] = dup(STDIN_FILENO);
	buffer[1] = dup(STDOUT_FILENO);
	if (buffer[0] == -1 || buffer[1] == -1)
		return (0);
	return (1);
}

int	restore_fds(int *buffer)
{
	int		flag;

	flag = 1;
	if (dup2(buffer[0], STDIN_FILENO) == -1)
		flag = 0;
	if (dup2(buffer[1], STDOUT_FILENO) == -1)
		flag = 0;
	close(buffer[0]);
	close(buffer[1]);
	return (flag);
}

int	single_builtin(t_data *data, t_cmd *cmd, t_exec *exec, int buffer[2])
{
	if (!buffer_fds(buffer))
		ft_exit(data, "dup");
	if (!open_files(cmd->redirs, exec))
		return (1);
	if (!dup_child(exec, 0))
		return (1);
	close_fds(exec);
	if (!ft_strcmp("echo", cmd->args[0]))
		bi_echo(data, cmd->args);
	else if (!ft_strcmp("cd", cmd->args[0]))
		bi_cd(data, cmd);
	else if (!ft_strcmp("pwd", cmd->args[0]))
		bi_pwd(data);
	else if (!ft_strcmp("export", cmd->args[0]))
		bi_export(data, cmd);
	else if (!ft_strcmp("unset", cmd->args[0]))
		bi_unset(data, cmd);
	else if (!ft_strcmp("env", cmd->args[0]))
		bi_env(data);
	else if (!ft_strcmp("exit", cmd->args[0]))
		bi_exit(data, cmd->args);
	if (!restore_fds(buffer))
		ft_exit(data, "dup");
	return (0);
}

int	executer(t_data *data)
{
	t_exec	exec;
	int		buffer[2];

	init_exec(data, &exec);
	sig_execute_parent();
	if (exec.cmd_count == 1 && data->cmd->args && data->cmd->args[0]
		&& isbuiltin(data->cmd->args[0]))
		data->ret = single_builtin(data, data->cmd, &exec, buffer);
	else
	{
		pipeline(data, data->cmd, &exec);
		waiting(data, &exec);
	}
	return (0);
}
