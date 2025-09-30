/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:21:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/30 13:38:10 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_path_free(char **path, char *buf[2], char *arg);
// {
// 	int i;

// 	if (path && )
// 	free_split(path);
// 	free(buf[0]);
// }

char	*get_path(t_data *data, t_cmd *cmd)
{
	char	*buf[2];
	char	**path;
	ssize_t	i;
 
	buf[0] = ft_strjoin("/", cmd->args[0]);
	if (!buf[0])
		return (NULL);
	path = ft_split(ms_getenv(data->env, "PATH"), ':');
	if (!path)
		return (free(buf[0]), NULL);
	i = -1;
	while (path[++i])
	{
		buf[1] = ft_strjoin(path[i], buf[0]);
		if (!buf[1])
			return (free_split(path), free(buf[0]), NULL);
		if (!access(buf[1], F_OK))
			break;
		else
			free(buf[1]);
	}
	if (path[i] && buf[1])
		return (free_split(path), free(buf[0]), buf[1]);
	else
		return (free_split(path), free(buf[0]), ft_strdup(cmd->args[0]));
}
