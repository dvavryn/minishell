/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:22 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:54:20 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	startup(&data, argc, argv, envp);
	while (1)
	{
		if (prompt(&data))
		{
			if (tokenize(&data))
				free_token(data.token);
			else
			{
				builtin_exit(&data);
				expander(&data);
				print_token(data.token);
				// parsing();
				// execution();
			}
			if (data.token)
				free_token(data.token);
			free(data.input);
		}
	}
}
