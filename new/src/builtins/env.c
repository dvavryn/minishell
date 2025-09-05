/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:19:22 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 14:30:18 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_env(t_data *data)
{
	ssize_t	i;

	i = -1;
	if (!data->envp)
		return ;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
}
