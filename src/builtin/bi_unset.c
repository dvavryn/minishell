/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:03:59 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 19:55:57 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	envsize(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static size_t	argsize(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

static int	bi_unset_sub(t_data *data, char *arg, size_t len)
{
	char	**out;
	size_t	size;
	ssize_t	i;
	size_t	j;

	size = envsize(data->env);
	out = ft_calloc(size, sizeof(char *));
	if (!out)
		ft_exit(data, "malloc");
	i = -1;
	j = 0;
	while (data->env[++i])
	{
		if (!(!ft_strncmp(data->env[i], arg, len)
				&& (data->env[i][len] == '=' || data->env[i][len] == '\0')))
		{
			out[j] = data->env[i];
			j++;
		}
	}
	if (data->env[i] == NULL && j == 0)
		return (free(out), 0);
	free(data->env);
	data->env = out;
	return (1);
}

int	bi_unset(t_data *data, t_cmd *cmd)
{
	ssize_t	i;

	i = 0;
	if (!cmd->args[1])
		return (0);
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] != '_')
		{
			if (!bi_unset_sub(data, cmd->args[i], argsize(cmd->args[i])))
				data->ret = 1;
		}
	}
	return (0);
}
