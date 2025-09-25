/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:10:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/26 15:04:33 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	free_array(char **arr, int count)
{
	while (--count >= 0)
		free(arr[count]);
	free(arr);
	return (0);
}

static int	ft_wordcount(char const *s, int c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	fillarray(char **dest, const char *s, char c)
{
	int		i;
	int		j;
	int		start;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			dest[j] = ft_substr(s, start, i - start);
			if (!dest[j])
				return (free_array(dest, j));
			j++;
		}
		else
			i++;
	}
	dest[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	if (!fillarray(dest, s, c))
		return (NULL);
	return (dest);
}
