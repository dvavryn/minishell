/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:05 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 21:08:08 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp, char *bin)
{
	char	*tmp;
	char	**out;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		write(2, "ERROR: NO PATH FOUND\n", 21);
		return (NULL);
	}
	tmp = ft_strdup(&envp[i][5]);
	if (!tmp)
	{
		write(2, "ERROR: MALLOC FAILED\n", 21);
		return (NULL);
	}
	out = ft_split_join(tmp, ':', bin);
	free(tmp);
	if (!out)
	{
		write(2, "ERROR: MALLOC FAILED\n", 21);
		return (NULL);
	}
	return (out);
}
