/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:58:26 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/15 17:05:13 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childs(t_data *data)
{
	t_cmd	*ptr;

	ptr = data->cmd;
	while (ptr)
	{
		wait(NULL);
		ptr = ptr->next;
	}
	return (0);
}

void	dups_files(t_data *data, t_cmd *cmd)
{
	int	fd;

	if (cmd->redir_in)
	{
		fd = open(cmd->file_in, O_RDONLY);
		if (fd == -1)
			ft_exit(data, "open");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->redir_out)
	{
		if (cmd->redir_out == R_OUT)
			fd = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->redir_out == R_APPEND)
			fd = open (cmd->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_exit(data, "open");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	dups_pipes(int pipe[2][2], size_t i, size_t count_cmds)
{
	if (i > 0)
		dup2(pipe[(i + 1) % 2][0], STDIN_FILENO);
	if (i < count_cmds - 1)
		dup2(pipe[i % 2][1], STDOUT_FILENO);
	if (pipe[0][0] != -1)
		close(pipe[0][0]);
	if (pipe[0][1] != -1)
		close(pipe[0][1]);
	if (pipe[1][0] != -1)
		close(pipe[1][0]);
	if (pipe[1][1] != -1)
		close(pipe[1][1]);
}

size_t	get_count_cmds(t_cmd *cmd)
{
	t_cmd	*ptr;
	size_t	out;

	out = 0;
	ptr = cmd;
	while (ptr)
	{
		out++;
		ptr = ptr->next;
	}
	return (out);
}

void	my_execve(t_data *data, t_cmd *cmd, int pipes[2][2], size_t	i)
{
	int				pid;
	size_t			count_cmds;

	count_cmds = get_count_cmds(data->cmd);
	if (i < count_cmds - 1)
	{
		if (pipe(pipes[i % 2]))
			ft_exit(data, "pipe");
	}
	pid = fork();
	if (pid == -1)
		ft_exit(data, "fork");
	if (!pid)
	{
		dups_pipes(pipes, i, count_cmds);
		dups_files(data, cmd);
		execve(cmd->args[0], cmd->args, data->env);
		ft_exit(data, "execve");
	}
	else
	{
		if (i > 0)
		{
			close(pipes[(i + 1) % 2][0]);
			close(pipes[(i + 1) % 2][1]);
		}
	}
}

void	executer(t_data *data)
{
	t_cmd	*ptr;
	int		pipes[2][2];
	size_t	i;

	if (!check_files(data))
		return ;
	if (!check_binaries(data))
		return ;
	get_all_args(data);
	ptr = data->cmd;
	i = 0;
	while (ptr)
	{
		my_execve(data, ptr, pipes, i);
		ptr = ptr->next;
		i++;
	}
	while (wait(NULL) > 0)
		;
}
