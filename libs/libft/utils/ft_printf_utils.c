/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:21:39 by bschwarz          #+#    #+#             */
/*   Updated: 2025/07/21 10:41:38 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	print_digit(unsigned long n, const char format)
{
	char				*base;
	unsigned int		con;

	if (format == 'u')
		con = 10;
	else
		con = 16;
	if (n >= con)
		print_digit(n / con, format);
	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	ft_printf_char(base[n % con]);
}

int	ft_printf_hex(unsigned long n, const char format)
{
	unsigned int	i;

	if (!n)
		return (ft_printf_number(n));
	print_digit(n, format);
	i = 0;
	while (n > 0)
	{
		if (format == 'u')
			n /= 10;
		else
			n /= 16;
		i++;
	}
	return (i);
}

int	ft_printf_number(int n)
{
	int		i;
	char	*fin;

	fin = ft_itoa(n);
	if (!fin)
		return (0);
	i = 0;
	while (fin[i])
		write(1, &fin[i++], 1);
	free (fin);
	return (i);
}

int	ft_printf_pointer(void *ptr)
{
	unsigned long	n;
	int				i;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	n = (unsigned long) ptr;
	write(1, "0x", 2);
	print_digit(n, 'x');
	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	i += 2;
	return (i);
}

int	ft_printf_string(char *str)
{
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}
