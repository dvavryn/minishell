/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/27 12:09:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path_type(char *bin)
{
	if (bin[0] == '.')
		return (RELATIVE);
	else if (bin[0] == '/')
		return (ABSOLUTE);
	return (SEARCH);
}
