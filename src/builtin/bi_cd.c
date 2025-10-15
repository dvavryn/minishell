/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:11:15 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 18:55:53 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_cd(t_data *data, t_cmd *cmd)
{
	char	*pwd;
	char	*tmp;
	ssize_t	i;
	
	pwd = ft_strdup(getcwd(NULL, 0));
	if (!cmd->args[1])
		chdir(ms_getenv(data->env, "HOME"));
	else if ((chdir(cmd->args[1])) == -1)
		return (perror("minishell: cd"), 0);
	if (!isexported(data->env, "OLDPWD"))
		add_env(data, "OLDPWD");
	if (!isexported(data->env, "PWD"))
		add_env(data, "PWD");
	if (!isexported(data->env, "OLDPWD") || !isexported(data->env, "PWD"))
		return (free(pwd), ft_exit(data, "malloc"), 1);

	i = -1;
	while (data->env[++i] && ft_strncmp(data->env[i], "OLDPWD", 6))
		;
	tmp = ft_strjoin("OLDPWD=", pwd);
	free(data->env[i]);
	data->env[i] = tmp;
	free(pwd);
	pwd = ft_strdup(getcwd(NULL, 0));
	i = -1;
	while (data->env[++i] && ft_strncmp(data->env[i], "PWD=", 4))
		;
	tmp = ft_strjoin("PWD=", pwd);
	free(data->env[i]);
	data->env[i] = tmp;
	free(pwd);
	return (0);
}

