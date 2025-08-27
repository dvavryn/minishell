/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:09:12 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/27 12:09:12 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd(int argc, char **argv)
{
	char	**out;
	ssize_t	i;

	out = ft_calloc(argc, sizeof(char *));
	if (!out)
		return (NULL);
	argv++;
	i = -1;
	while (argv[++i])
	{
		out[i] = ft_strdup(argv[i]);
		if (!out[i])
		{
			free_split(out);
			return (NULL);
		}
	}
	out[i] = NULL;
	return (out);
}
