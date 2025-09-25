/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:31:11 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/26 15:04:21 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_char(int c)
{
	return (write(1, &c, 1));
}

static int	ft_check(va_list args, const char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_printf_char(va_arg(args, int));
	else if (format == 's')
		i += ft_printf_string(va_arg(args, char *));
	else if (format == 'p')
		i += ft_printf_pointer(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		i += ft_printf_number(va_arg(args, int));
	else if (format == 'x' || format == 'X' || format == 'u')
		i += ft_printf_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		i += write(1, "%", 1);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (str == NULL || !str)
		return (-1);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			count += ft_check(args, str[i]);
		}
		else
			count += ft_printf_char(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
