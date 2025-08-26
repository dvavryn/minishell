/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_permissions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:04:17 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 21:04:17 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	test_permissions(char *exe)
{
	if (access(exe, F_OK))
	{
		write(2, "no such file or directory: ", 28);
		write(2, exe, ft_strlen(exe));
		write(2, "\n", 1);
		free(exe);
		return (1);
	}
	else if (access(exe, X_OK))
	{
		write(2, "Permission denied!\n", 20);
		free(exe);
		return (2);
	}
}
