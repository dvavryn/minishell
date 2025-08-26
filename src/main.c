/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:32 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/26 15:34:09 by bschwarz         ###   ########.fr       */
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
			print_tokens(token);
			free_tokens(token);
		}
	}
}
