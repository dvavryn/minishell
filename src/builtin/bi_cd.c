/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:11:15 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 16:16:50 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_cd(t_data *data, t_cmd *cmd)
{
	char **env = data->env;
	char *new_dir = cmd->args[1];
	// if !cmd->args[0] ... chdir to $HOME
	char *pwd;
	
	ssize_t	i = -1;
	while (env[++i] && !ft_strncmp("PWD=", env[i], 4))
		;
	if (!env[i])
		// wtf?
		;
	pwd = env[i];

	char *old_pwd;
	
	i = -1;
	while (env[++i] && !ft_strncmp("OLDPWD=", env[i], 4))
		;
	if (!env[i])
		// create OLDPWD and !!!join!!! -- is fun, not -- to env
		;
	oldpwd = env[i];

	(void)data;
	(void)cmd;
	return (0);
}