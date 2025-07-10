/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:25 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/10 13:39:06 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokenize(char *input)
{
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
		
	print_startup();
	while (1)
	{
		data.input = readline("minishell> ");
		if (!data.input || !*data.input)
			;
		else
			add_history(data.input);
		if (!strncmp(data.input, "echo", 4))
			printf("%s\n", data.input + 5);
		else if (!strncmp(data.input, "exit", 5))
			exit(0);
		else if (!strncmp(data.input, "clear", 5))
		{
			char **split = ft_split(data.input, ' ');
			int id;
			id = fork();
			if (!id)
				execve("/usr/bin/clear", split + 1, envp);
			else
				wait(NULL);
		}
		tokenize(data.input);
		free(data.input);
	}
}
