/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:45:47 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 16:46:08 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_hd_sub(char *in, char **out, size_t i, size_t j)
{
	size_t	len;
	char	q;

	len = ft_strlen(in);
	q = 0;
	while (i < len)
	{
		if (!q)
		{
			if (in[i] == '"' || in[i] == '\'')
				q = in[i++];
			else
				(*out)[j++] = in[i++];
		}
		else
		{
			if (in[i] == q)
			{
				q = 0;
				i++;
			}
			else
				(*out)[j++] = in[i++];
		}
	}
}

char	*clean_hd(char *in)
{
	char	*out;

	out = ft_calloc(1, ft_strlen(in) + 1);
	if (!out)
		return (NULL);
	clean_hd_sub(in, &out, 0, 0);
	return (out);
}
