/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:57:06 by bschwarz          #+#    #+#             */
/*   Updated: 2025/07/21 10:40:11 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	unsigned int	i;

	src1 = (unsigned char *) s1;
	src2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && src1[i] == src2[i])
	{
		i++;
	}
	return ((unsigned char) src1[i] - (unsigned char) src2[i]);
}
