/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:57:30 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/15 19:53:28 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo(t_data *data, char **args)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
		i = 1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			if ((write(STDOUT_FILENO, &args[i][j], 1)) == -1)
				return (-1);
		if (args[i + 1])
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (-1);
	}
	if (args[1] && ft_strcmp(args[1], "-n"))
		if ((write(STDOUT_FILENO, "\n", 1)) == -1)
			return (-1);
	return (0);
	(void)data;
}
