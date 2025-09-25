/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:22:44 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 15:22:45 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(t_data	*data, char **args)
{
	int	ret;

	printf("exit\n");
	if (!args || !args[1])
		ret = 0;
	else
		ret = ft_atoi(args[1]);
	free_all(data);
	exit(ret);
}
