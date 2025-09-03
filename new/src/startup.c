/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:28 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:42:52 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	startup(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	data->envp = copy_split(envp);
	if (!data->envp)
		ft_exit(data, MAL_ERR, 1);
}
