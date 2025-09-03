/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:28 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 23:26:55 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_own(char **envp)
{
	if (envp[0])
		free(envp[0]);
	if (envp[1])
		free(envp[1]);
	if (envp[2])
		free(envp[2]);
	if (envp[3])
		free(envp[3]);
	free(envp);
}

static char	**set_own(void)
{

	// TODO!!!!!!!!!!
	char **out;

	// ===================================
	// 
	// 		WHY DONT YOU FUCKER WORK
	//
	// ===================================
	out = ft_calloc(5, sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = ft_strdup("PATH=/"); //PWD=
	out[1] = ft_strdup("SHLVL=/"); //SHLVL=
	out[2] = ft_strdup("PATH=/trololololo/:"); //PATH=
	out[3] = ft_strdup("_=/"); //_=
	if (!out[0] || !out[1] || !out[2] || !out[3])
		free_own(out);
	return (out);
}

void	startup(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	if (!envp || !envp[0])
		data->envp = set_own();
	else
		data->envp = copy_split(envp);
	if (!data->envp)
		ft_exit(data, MAL_ERR, 1);
}
