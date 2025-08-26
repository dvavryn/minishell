/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:21 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 21:05:21 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_access(char **path)
{
	ssize_t	i;
	char	*out;

	i = -1;
	while (path[++i] && access(path[i], F_OK))
		;
	if (!path[i])
	{
		out = NULL;
		write(2, "No such file or directory\n", 26);
	}
	else
		out = ft_strdup(path[i]);
	free_split(path);
	return (out);
}
