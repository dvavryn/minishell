/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:29:40 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/15 17:05:49 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	split_size(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**merge_split(char **arr1, char **arr2)
{
	size_t	i;
	ssize_t	j;
	char	**out;

	out = ft_calloc(split_size(arr1) + split_size(arr2) + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = -1;
	while (arr1 && arr1[++j])
	{
		out[i] = ft_strdup(arr1[j]);
		if (!out[i])
			return (free_split(out), NULL);
		i++;
	}
	j = -1;
	while (arr2 && arr2[++j])
	{
		out[i] = ft_strdup(arr2[j]);
		if (!out[i])
			return (free_split(out), NULL);
		i++;
	}
	return (out);
}
