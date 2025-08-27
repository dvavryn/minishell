/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:32 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 12:37:07 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token	*token;
	char	*input;

	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		else if (*input == 0)
		{
			free(input);
		}
		else
		{
			add_history(input);
			token = lex_input(input);
			if (!ft_strncmp("exe", token->value, ft_strlen(token->value)))
			{
				ft_executor(token->next);
			}
			else
				print_tokens(token);
			
			free_tokens(token);
		}
	}
}
