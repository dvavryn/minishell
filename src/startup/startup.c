/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:07:22 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 19:42:37 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**empty_env(void)
{
	char	**out;

	out = ft_calloc(5, sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = ft_strdup(getcwd(NULL, 0));
	if (!out[0])
		return (free_split(out), NULL);
	out[1] = ft_strdup("SHLVL=1");
	if (!out[1])
		return (free_split(out), NULL);
	out[2] = ft_strdup("_=/usr/bin/env");
	if (!out[2])
		return (free_split(out), NULL);
	out[3] = ft_strdup("OLDPWD");
	if (!out[3])
		return (free_split(out), NULL);
	return (out);
}

char	*set_var(char *env)
{
	char	*out;
	char	*tmp;

	if (!ft_strncmp(env, "SHLVL=", 6))
	{
		tmp = ft_itoa(ft_atoi(&env[6]) + 1);
		if (!tmp)
			return (NULL);
		out = ft_strjoin("SHLVL=", tmp);
		free(tmp);
		return (out);
	}
	else
		return (ft_strdup(env));
}

char	**copy_env(char **envp)
{
	char	**out;
	ssize_t	i;

	if (!envp || !*envp)
		return (empty_env());
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && envp[i] != NULL)
		i++;
	out = ft_calloc(i + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		out[i] = set_var(envp[i]);
		if (!out[i])
			return (free_split_rev(out, i), NULL);
		i++;
	}
	if (!out)
		return (NULL);
	return (out);
}

void	startup(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	data->env = copy_env(envp);
	if (!data->env)
		ft_exit(data, "memory allocation");
}
