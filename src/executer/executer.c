/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:05:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/01 13:48:47 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	waiting(t_data *data, t_exec *exec)
{
	t_cmd	*ptr;

	ptr = data->cmd;
	while (ptr)
	{
		waitpid(-1, &exec->status, 0);
		if (WIFEXITED(exec->status))
			data->ret = WEXITSTATUS(exec->status);
		else if (WIFSIGNALED(exec->status))
		{
			printf("TERMINATED BY SIGNAL: %d\n", WTERMSIG(exec->status));
			data->ret = 128 + WTERMSIG(exec->status);
		}
		ptr = ptr->next;
	}
}

static void	single_builtin(t_data *data, t_cmd *cmd, t_exec *exec)
{
	(void)data;
	(void)cmd;
	(void)exec;
	return ;
}

int	executer(t_data *data)
{
	t_exec	exec;

	init_exec(data, &exec);
	if (exec.cmd_count == 1 && isbuiltin(data->cmd->args[0]))
		single_builtin(data, data->cmd, &exec);
	else
	{
		sig_execute_parent();
		pipeline(data, data->cmd, &exec);
		waiting(data, &exec);
	}
	return (0);
}
