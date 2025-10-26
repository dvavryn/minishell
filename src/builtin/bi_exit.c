/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@sudent.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:22:44 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/26 15:11:10 by dvavryn          ###   ########.fr       */
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
	{
		ret = ft_atoi(args[1]);
		if (ret == 0 && args[1][0] != 0)
		{
			ft_putstr_fd("minishell: ", STDOUT_FILENO);
			ft_putstr_fd(args[1], STDOUT_FILENO);
			ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
			data->ret = 2;
			return ;
		}
	}
	free_all(data);
	exit(ret);
}
