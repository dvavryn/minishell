/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:47:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/14 16:43:33 by dvavryn          ###   ########.fr       */
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
	printf("%s\n", ms_getenv(data->env, tmp));
	free(tmp);
	return (0);
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
	char *new = ft_strjoin(ft_substr(cmd->args[1], 0, j), ft_substr(cmd->args[1], j+k, ft_strlen(&cmd->args[1][j+k]) - k));
	if (!new)
		ft_exit(data, "malloc");
	// else
		// printf("%s\n", new);
	free(data->env[i]);
	data->env[i] = new;		
	return (0);
}