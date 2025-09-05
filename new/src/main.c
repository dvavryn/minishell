/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:22 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 17:42:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	startup(&data, argc, argv, envp);
	while (1)
	{
		data.token = NULL;
		data.input = NULL;
		if (prompt(&data))
		{
			if (tokenize(&data))
			{
				free_token(data.token);
				printf("fuck\n");
			}
			else
			{
				builtin_exit(&data);
				expander(&data);
				// if (parser(&data))
				// {
				// 	printf("noice\n");
				// }
				print_token(data.token);
				free_token(data.token);
			}
			free(data.input);
		}
	}
}
