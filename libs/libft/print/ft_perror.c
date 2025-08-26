/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:04:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/26 15:04:19 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_check(const char format)
{
	if (format == 's')
		write(2, "syntaxerror", 12);
}

void	ft_perror(const char *str)
{
	ssize_t	i;

	if (str == NULL || !str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			ft_check(str[i]);
		}
		else
			write(2, &str[i], 1);
	}
}
