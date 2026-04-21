/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_endl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:46:43 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 16:47:41 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_endl(char *s1, char *s2)
{
	char	*out;
	ssize_t	i;
	ssize_t	j;

	out = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!out)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		out[++j] = s1[i];
	i = -1;
	while (s2[++i])
		out[++j] = s2[i];
	out[++j] = '\n';
	out[++j] = 0;
	return (out);
}
