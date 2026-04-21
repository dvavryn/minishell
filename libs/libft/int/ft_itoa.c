/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:54:35 by bschwarz          #+#    #+#             */
/*   Updated: 2025/07/21 10:39:14 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_dlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*fillstr(int n)
{
	size_t		i;
	size_t		len;
	char		*fin;

	i = 0;
	len = ft_dlen(n);
	fin = malloc(len + 1 * sizeof(char));
	if (!fin)
		return (NULL);
	while (i < len)
		fin[i++] = '0';
	fin[len--] = '\0';
	if (n < 0)
	{
		fin[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		fin[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (fin);
}

char	*ft_itoa(int n)
{
	char	*fin;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	fin = fillstr(n);
	if (!fin)
		return (NULL);
	return (fin);
}
