/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:29:40 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/11 13:05:24 by dvavryn          ###   ########.fr       */
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

char **merge_split(char **arr1, char **arr2)
{
	size_t	i;
	ssize_t	j;
	char **out;

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

// int main(void)
// {
// 	char **arr1 = ft_split("hello world i am a string", ' ');
// 	if (!arr1)
// 		return (1);
// 	// char **arr2 = ft_split("lol that really worked", ' ');
// 	// if (!arr2)
// 	// 	return (free_split(arr1), 1);
// 	char **out = merge_split(NULL, arr1);
// 	if (!out)
// 		return (free_split(arr1), /*free_split(arr2),*/ 1);
// 	for (int i = 0; out[i]; i++)
// 		printf("%s\n", out[i]);
// 	free_split(arr1);
// 	// free_split(arr2);
// 	free_split(out);
// }