/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:10:24 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/25 14:35:08 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("0\n");	
		if (token->type == TOKEN_WORD)
		{
			printf("1\n");	
			printf("Token: %s Type: WORD\n", token->value);
		}
		else if (token->type == TOKEN_PIPE)
		{
			printf("2\n");	
			printf("Token: %s Type: PIPE\n", token->value);
		}
		token = token->next;
	}
}

// int	main(int ac, char **av)
// {
// 	t_token	*tokens;
	
// 	if (ac != 2)
// 		return (0);
// 	tokens = lex_input(av[1]);
// 	print_tokens(tokens);
// 	free_tokens(tokens);
// }
