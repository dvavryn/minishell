/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:12:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/11 17:04:53 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	bi_export(t_data *data, t_cmd *cmd)
{
	char	**buf;
	size_t	i;

	// printf("here");
	if (!cmd->args || !cmd->args[0] || !cmd->args[1])
		return (printf("todo: print!\n"), 0);
	i = 0;
	while (cmd->args[++i])
	{
		if (cmd->args[i] && ft_strchr(cmd->args[i], '='))
		{
			buf = add_split(data->env, cmd->args[i]);
			if (!buf)
				ft_exit(data, "malloc");
			free_split(data->env);
			data->env = buf;
		}
	}
	return (0);
}


// int bi_export(t_data *data, t_cmd *cmd, int ft)
// {
// 	data->env = realloc(data->env, sizeof(data->env) + sizeof(char *));
	
// 	size_t	i;
// 	while (data->env[i])
// 		i++;
// 	data->env[i] = strdup(cmd->args[1]);
// }