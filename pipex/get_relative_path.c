/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:56:20 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 21:03:47 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	loop(char *bin, size_t *i, char **tmp, char **out);

char	*get_relative_path(char	*bin)
{
	size_t	i;
	char	*out;
	char	*tmp;

	out = getcwd(NULL, 0);
	if (!out)
		return (NULL);
	i = 0;
	while (bin[i] && bin[i] == '.')
	{
		if (!loop(bin, &i, &tmp, &out))
			return (NULL);
	}
	tmp = out;
	out = ft_strjoin(out, &bin[i - 1]);
	free(tmp);
	if (!out)
		return (NULL);
	return (out);
}

static int	loop(char *bin, size_t *i, char **tmp, char **out)
{
	if (ft_strlen(&bin[*i]) >= 2 && !ft_strncmp("./", &bin[*i], 2))
		*i += 2;
	else if (ft_strlen(&bin[*i]) >= 3 && !ft_strncmp("../", &bin[*i], 3))
	{
		*i += 3;
		*tmp = *out;
		*out = shorten_path(*out);
		free(*tmp);
		*tmp = NULL;
		if (!out)
			return (0);
	}
	return (1);
}
