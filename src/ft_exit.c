/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:14:02 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 15:14:05 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char *error)
{
	if (!ft_strcmp("malloc", error))
		write(2, "minishell: error: memory allocation failed\n", 43);
	if (!ft_strcmp("fork", error))
		write(2, "minishell: error: fork failed\n", 31);
	if (!ft_strcmp("open", error))
		write(2, "minishell: error: open failed\n", 30);
	if (!ft_strcmp("pipe", error))
		write(2, "minishell: error: pipe failed\n", 31);
	free_all(data);
	exit(1);
}
