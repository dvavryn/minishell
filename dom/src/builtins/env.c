/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:12:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/11 17:05:56 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_data *data)
{
	size_t	i;

	if (!data->env)
		return ;
	if (!data->env[0])
		return ;
	i = 0;
	while (data->env[i])
	{
		ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
}
