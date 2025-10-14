/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:27:48 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/14 12:07:08 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (data->env[++i])
	{
		write(STDOUT_FILENO, data->env[i], ft_strlen(data->env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
