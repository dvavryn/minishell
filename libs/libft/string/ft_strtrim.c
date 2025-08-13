/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:05:50 by bschwarz          #+#    #+#             */
/*   Updated: 2025/07/21 10:41:20 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_check(char const src, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (src == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		start;
	int		end;
	int		j;

	if (!s1)
		return (NULL);
	end = ft_strlen((char *)s1);
	start = 0;
	while (s1[start] && ft_check(s1[start], set))
		start++;
	while (end != 0 && ft_check(s1[end - 1], set))
		end--;
	if (start > end)
		dest = malloc(1 * sizeof(char));
	else
		dest = malloc((end - start + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	j = 0;
	while (s1[start] && start < end)
		dest[j++] = s1[start++];
	dest[j] = '\0';
	return (dest);
}
