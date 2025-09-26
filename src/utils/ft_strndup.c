/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:14:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 12:15:02 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;
	size_t	i;

	if (!s || !n)
		return (NULL);
	out = (char *)malloc((n + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
