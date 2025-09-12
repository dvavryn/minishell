/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:02:25 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/12 13:26:17 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	split_size(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr || !*arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char **add_split(char **arr1, char *str)
{
	size_t	i;
	char **out;
	size_t	size;
	
	printf("here i am\n");
	size = split_size(arr1) + 2;
	out = NULL;
	out = ft_calloc(size, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (arr1[i])
	{
		out[i] = ft_strdup(arr1[i]);
		if (!out[i])
			return (free_split(out), NULL);
		i++;
	}
	out[i] = ft_strdup(str);
	if (!out[i])
		return (free_split(out), NULL);
	return (out);
}
