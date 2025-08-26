/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shorten_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:03:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 21:03:53 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*shorten_path(char	*str)
{
	ssize_t	i;
	char	*ptr;

	i = -1;
	ptr = ft_strrchr(str, '/');
	while (&str[++i] != ptr || ptr + 1 == 0)
		;
	return (ft_substr(str, 0, i));
}
