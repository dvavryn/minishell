/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:08:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 17:02:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_split_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**split_copy(char **arr)
{
	char	**out;
	ssize_t	i;

	out = ft_calloc(get_split_size(arr) + 2, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		out[i] = ft_strdup(arr[i]);
		if (!out[i])
		{
			while (--i >= 0)
				free(out[i]);
			free(out);
			return (NULL);
		}
	}
	return (out);
}
