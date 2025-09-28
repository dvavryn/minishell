/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:05:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/28 14:11:02 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exec
{
	int	pid;
	int		pipe[2][2];
	size_t	cmd_count;
}	t_exec;

void	init_exec(t_data *data, t_exec *exec)
{
	t_cmd	*ptr;

	ft_memset(&exec->pid, -1, sizeof(int));	
	ft_memset(&exec->pipe, -1, 4 * sizeof(int));
	ptr = data->cmd;
	exec->cmd_count = 0;
	while (ptr)
	{
		exec->cmd_count++;
		ptr = ptr->next;
	}
}

int executer_no_fork()
{
	return (0);
}
int executer_fork()
{
	return (0);
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

int executer(t_data *data)
{
	t_exec exec;

	init_exec(data, &exec);

	if (exec.cmd_count == 1)
	{
		if (isbuiltin(data->cmd->cmd))
			executer_no_fork();
		else
		{
			t_redir *ptr;
			int fd_in;
			int	fd_out;

			fd_in = -1;
			fd_out = -1;
			ptr = data->cmd->redirs;
			while (ptr)
			{
				if (ptr->type == R_IN)
				{
					if (fd_in != -1)
						close(fd_in);
					fd_in = open(ptr->filename, O_RDONLY);
					if (fd_in == -1)
					{
						perror(ptr->filename);
						data->ret = -1; //change
						break ;
					}
				}
				else if (ptr->type == R_OUT)
				{
					if (fd_out != -1)
						close(fd_out);
					fd_out = open(ptr->filename, O_RDONLY | O_CREAT | O_TRUNC, 0600);
					if (fd_out == -1)
					{
						perror(ptr->filename);
						data->ret = -1; //change
						break ;
					}
				}
				else if (ptr->type == R_APPEND)
				{
					if (fd_out != -1)
						close(fd_out);
					fd_out = open(ptr->filename, O_RDONLY | O_CREAT | O_APPEND, 0600);
					if (fd_out == -1)
					{
						perror(ptr->filename);
						data->ret = -1; //change
						break ;
					}
				}
				ptr = ptr->next;	
			}
		}
	}
	else
		executer_fork();
	return (1);
}
