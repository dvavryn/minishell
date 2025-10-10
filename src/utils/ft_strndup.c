/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:14:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/10 15:11:26 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;
	size_t	i;

	if (!s)
		return (NULL);
	out = malloc(n + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
