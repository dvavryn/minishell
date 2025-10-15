/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:03:40 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 15:52:43 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	// update shelllvl
	startup(&data, argc, argv, envp);
	while (1)
	{
		sig_interactive();
		if (prompt(&data))
		{
			tokenize(&data);
			if (data.tokens)
			{
				expander(&data);
				expanded_tokens(&data);
				if (parser(&data))
				{
					if (!data.hd_quit)
						executer(&data);
					else
						data.hd_quit = 0;
					free_cmd(data.cmd);
					data.cmd = NULL;
				}
			}
			free_tokens(data.tokens);
			data.tokens = NULL;
			free(data.input);
		}
	}
}
