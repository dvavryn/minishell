/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:12:26 by bschwarz          #+#    #+#             */
/*   Updated: 2025/07/21 10:40:16 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (dest > src)
	{
		while (n--)
			d[n] = s[n];
	}
	else if (dest < src)
	{
		while (n > i)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
