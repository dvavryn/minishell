/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:47:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/14 17:07:31 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_var()
{
	return (0);	
}

int	add_export_list()
{
	return (0);
}

int bi_export(t_data *data, t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		printf("export-list\n");
		return (0);
	}
	
	size_t	i = 0;
	size_t	j = 0;
	char *ptr;

	while (cmd->args[1][j] && cmd->args[1][j] != '=')
		j++;
	char *tmp = ft_substr(cmd->args[1], 0, j);
	if (!tmp)
		ft_exit(data, "malloc");
	if (ms_getenv(data->env, tmp))
	{
		while (data->env[i])
		{
			if (!ft_strncmp(data->env[i], cmd->args[1], j))
			{
				ptr = data->env[i];
				break ;
			}
			i++;
		}
		size_t k = 0;
		if (cmd->args[1][j + 1] == '"')
			k = 1;

		char *aa = ft_substr(cmd->args[1], 0, j);
		char *bb = ft_substr(cmd->args[1], j+k, ft_strlen(&cmd->args[1][j+k]) - k);
		if (!aa)
		{
			free(tmp);	
			ft_exit(data, "malloc");
		}
		if (!bb)
		{
			free(tmp);
			free(aa);
			ft_exit(data, "malloc");
		}
		char *new = ft_strjoin(aa, bb);
		free(aa);
		free(bb);
		if (!new)
			return (free(tmp), ft_exit(data, "malloc"), 1);
		free(data->env[i]);
		data->env[i] = new;		
	}
	// else
		// printf("%s\n", new);
	free(tmp);
	return (0);
}