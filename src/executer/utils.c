/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:50:29 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 20:54:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	isbuiltin(char *s)
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
	return (0);
}

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
