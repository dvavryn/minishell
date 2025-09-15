/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:47:47 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/15 17:00:30 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*ms_getcwd(void)
{
	char	*out;
	char	*tmp1;

	tmp1 = getcwd(NULL, 0);
	if (!tmp1)
		return (NULL);
	out = ft_strjoin("PWD=", tmp1);
	free(tmp1);
	if (!out)
		return (NULL);
	return (out);
}

static char	**empty_env(void)
{
	char	**out;

	out = ft_calloc(4, sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = ms_getcwd();
	if (!out[0])
		return (free_split(out), NULL);
	out[1] = ft_strdup("SHLVL=1");
	if (!out[1])
		return (free_split(out), NULL);
	out[2] = ft_strdup("_=/usr/bin/env");
	if (!out[2])
		return (free_split(out), NULL);
	return (out);
}

static char	**copy_env(char **envp)
{
	char	**out;
	ssize_t	i;

	if (!envp || !*envp)
		return (empty_env());
	if (!envp)
		exit(3);
	i = 0;
	while (envp[i] && envp[i] != NULL)
		i++;
	out = ft_calloc(i + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		out[i] = ft_strdup(envp[i]);
		if (!out[i])
			return (free_split_rev(out, i), NULL);
		i++;
	}
	return (out);
}

void	startup(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	ft_bzero(data, sizeof(t_data));
	data->env = copy_env(envp);
	if (!data->env)
		ft_exit(data, "malloc");
}
