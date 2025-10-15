/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:11:15 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 17:47:11 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_cd(t_data *data, t_cmd *cmd)
{
	char	*new_dir = cmd->args[1];
	char	*pwd;
	char	*tmp;
	// char *oldpwd;
	
	if (!cmd->args[1])
		chdir("/home");
	else if ((chdir(new_dir)) == -1)
		return (perror("minishell: cd"), 0);
	pwd = ft_strdup(getcwd(NULL, 0));
	// printf("pwd: %s\n", pwd);
	ssize_t	i = -1;
	while (data->env[++i] && !ft_strncmp("PWD=", data->env[i], 4))
		;
	if (!data->env[i])
		printf("wtf?\n");
		;
	tmp = data->env[i];
	// printf("tmp: %s\n", tmp);
	data->env[i] = ft_strjoin("PWD=", pwd);
	free(tmp);
	free(pwd);

	// char *old_pwd;
	
	// i = -1;
	// while (env[++i] && !ft_strncmp("OLDPWD=", env[i], 4))
	// 	;
	// if (!env[i])
	// 	// create OLDPWD and !!!join!!! -- is fun, not -- to env
	// 	;
	// oldpwd = env[i];
	(void)new_dir;
	return (0);
}