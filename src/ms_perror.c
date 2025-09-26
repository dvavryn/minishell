/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:47:50 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/26 12:04:45 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_perror_string(char *str, char c)
{
	if (!str)
		return ;
	write(STDERR_FILENO, str, ft_strlen(str));
	if (c == 'f')
		write(STDERR_FILENO, " failed", 8);
}

static void	ms_perror_digit(int d)
{
	char	*digit;

	digit = ft_itoa(d);
	if (!digit)
		return ;
	d = -1;
	while (digit[++d])
		write(STDERR_FILENO, &digit[d], 1);
	free(digit);
}

static ssize_t	ms_perror_prefix(const char *str)
{
	if (*str && *str + 1 && str[0] == 'M' && str[1] == 'S')
		return (ms_perror_string("minishell: error: ", 's'), 2);
	return (0);
}

void	ms_perror(const char *str, ...)
{
	ssize_t	i;
	va_list	args;

	if (!str || !*str)
		return ;
	va_start(args, str);
	i = -1;
	i += ms_perror_prefix(str);
	while (str[++i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == 's' || str[i] == 'f')
				ms_perror_string(va_arg(args, char *), str[i]);
			else if (str[i] == 'd')
				ms_perror_digit(va_arg(args, int));
			else if (str[i] == '%')
				write(STDERR_FILENO, '%', 1);
		}
		else
			write(STDERR_FILENO, &str[i], 1);
	}
	va_end(args);
}
