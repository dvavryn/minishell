/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:04:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 21:04:59 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split_join(char *to_split, char sep, char *to_join)
{
	char	**out;
	char	*tmp;
	char	*tmp2;
	ssize_t	i;

	if (!to_split || !sep)
		return (NULL);
	out = ft_split(to_split, sep);
	if (!out)
		return (NULL);
	if (to_join)
	{
		i = -1;
		while (out[++i])
		{
			tmp = ft_strjoin(out[i], "/");
			if (!tmp)
				return (free_split(out), NULL);
			tmp2 = ft_strjoin(tmp, to_join);
			free(tmp);
			if (!tmp2)
				return (free_split(out), NULL);
			free(out[i]);
			out[i] = tmp2;
		}
	}
	return (out);
}
