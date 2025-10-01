/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:50:29 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/01 13:48:21 by dvavryn          ###   ########.fr       */
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
