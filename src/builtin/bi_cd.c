/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:11:15 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 21:12:01 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int assign_pwd(t_data *data, char *pwd, ssize_t i)
{
	char	*tmp;
	char	*path;
	char	**buf;

	path = getcwd(NULL, 0);
	while (data->env[i] && ft_strncmp(data->env[i], pwd, (ft_strlen(pwd) - 1)))
		i++;
	if (!data->env[i])
	{
		buf = ft_calloc(i + 2, sizeof(char *));
		if (!buf)
			return (free(path), 1);
		i = -1;
		while (data->env[++i])
			buf[i] = data->env[i];
		buf[i++] = ft_strjoin(pwd, path);
		buf[i] = NULL;
		return (free(path), 0);
	}
	else
		tmp = ft_strjoin(pwd, path);
	if (!tmp)
		return (free(path), 1);
	free(data->env[i]);
	data->env[i] = tmp;
	return (free(path), 0);
}

int	bi_cd(t_data *data, t_cmd *cmd)
{	
	char	*old;
	
	if (!ms_getenv(data->env, "OLDPWD"))
		old = NULL;
	else
		old = ft_strdup(ms_getenv(data->env, "OLDPWD"));
	if(assign_pwd(data, "OLDPWD=", 0))
		return (1);
	if (!cmd->args[1])
		chdir(ms_getenv(data->env, "HOME"));
	else if (cmd->args[1][0] == '-')
		chdir(old);
	else if ((chdir(cmd->args[1])) == -1)
		return (perror("minishell: cd"), 1);
	if (assign_pwd(data, "PWD=", 0))
		return (1);
	return (0);
}
