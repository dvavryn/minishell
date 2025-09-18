/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:12:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 17:45:02 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char **add_env(t_data *data, char *s)
// {
// 	char **out;

// 	out = add_split(data->env, s);
// 	free_split(data->env);
// 	if (!out)
// 		return (NULL);
// 	return (out);
// }

// int	env_exists(t_data *data, char *arg)
// {
// 	ssize_t	i;
// 	ssize_t	j;
// 	i = -1;
	
// 	while ()
// 	while (ft_strcmp(data->env[i], arg))
// }


int	bi_export(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	size_t	i;

	if (!cmd->args || !cmd->args[0] || !cmd->args[1])
		return (printf("todo: print!\n"), 0);
	i = 0;
	while (cmd->args[++i])
	{
		if (cmd->args[i] && ft_strchr(cmd->args[i], '='))
		{
			// if (!env_exist(data->env))
			// 	data->env = add_env(data, cmd->args[i]);
			// else
			// 	data->env = replace_env(data, cmd->args[i]);				
			// if (!data->env)
			// 	ft_exit(data, "malloc");
		}
	}
	return (0);
}
