/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:05:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/27 20:15:01 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int executer(t_data *data)
{
	int		pid;
	int		pipes[2][2];
	t_cmd	*ptr;
	ft_memset(&pipes, -1, sizeof(int) * 4);
	
	
	return (1);
}