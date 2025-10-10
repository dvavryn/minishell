/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:57:30 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/10 15:15:17 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo(t_data *data, t_cmd *cmd, char **args)
{
	ssize_t	i;
	ssize_t	j;
	
	(void)data;
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			if ((write(1, &args[i][j], 1)) == -1)
				return (-1);
		if (args[i + 1])
			if ((write(1, " ", 1)) == -1)
				return (-1);	
	}
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
		if ((write(1, "\n", 1)) == -1)
			return (-1);
	return (0);
}
