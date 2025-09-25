/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:12:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/12 12:35:52 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo_sub(t_cmd *cmd, size_t *i)
{
	int	n;

	n = 0;
	*i = 1;
	while (cmd->args[*i] && !ft_strncmp("-n", cmd->args[*i], 2))
	{
		n = -1;
		(*i)++;
	}
	return (n);
}

int	bi_echo(t_cmd *cmd)
{
	size_t	i;
	int		n;

	n = bi_echo_sub(cmd, &i);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n)
		ft_putendl_fd("", STDOUT_FILENO);
	return (0);
}
