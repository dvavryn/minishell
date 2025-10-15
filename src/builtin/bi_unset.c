/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:03:59 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 15:25:51 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_unset(t_data *data, t_cmd *cmd, char **export_list)
{
	(void)data;
	(void)cmd;
	(void)export_list;
	return (0);
}

// int	bi_unset(t_data *data, t_cmd *cmd, char **export_list)
// {
// 	// size_t	i;
// 	// char **out;
// 	// char *to_free;
// 	// (void)export_list;

// 	// if (!cmd->args[1])
// 	// 	return 0;
// 	// i = 0;
// 	// while (data->env[i])
// 	// 	i++;
// 	// out = ft_calloc(i, sizeof(char *));
// 	// if (!out)
// 	// 	return (1);
// 	// size_t j = 0;
// 	// i = 0;
// 	// size_t	k;

// 	// k = 0;
// 	// while (cmd->args[k])
// 	// {
// 	// 	i = 0;
// 	// 	if (ms_getenv(data->env, cmd->args[k]))
// 	// 	{
// 	// 		while (data->env[i])
// 	// 		{
// 	// 			if (!ft_strncmp(data->env[i], cmd->args[k],
	// ft_strlen(cmd->args[k]) && data->env[i][ft_strlen(cmd->args[k]) + 1]))
// 	// 				to_free = data->env[i];
// 	// 			else
// 	// 			{
// 	// 				out[j] = ft_strdup(data->env[i]);
// 	// 				j++;
// 	// 			}
// 	// 			i++;
// 	// 		}
// 	// 		free_split(data->env);
// 	// 		data->env = out;
// 	// 	}
// 	// 	k++;
// 	// }
// 	return (0);
// 	(void)data;
// 	(void)cmd;
// 	(void)export_list;
// }
