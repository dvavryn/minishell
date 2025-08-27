/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:10:24 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 11:42:45 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
}

void	print_tokens(t_token *token)
{
	char	*quote;

	if (token)
	{
		printf("\n");
		while (token)
		{
			if (token->quote == 0)
				quote = ft_strdup("NONE");
			else if (token->quote == 1)	
				quote = ft_strdup("SINGLE");
			else if (token->quote == 2)
				quote = ft_strdup("DOUBLE");
			if (token->type == TOKEN_WORD)
			printf("Token: %s Type: WORD Quote: %s\n", token->value, quote);
			else if (token->type == TOKEN_REDIR_IN)
			printf("Token: %s Type: RED_IN Quote: %s\n", token->value, quote);
			else if (token->type == TOKEN_REDIR_OUT)
			printf("Token: %s Type: RED_OUT Quote: %s\n", token->value, quote);		
			else if (token->type == TOKEN_PIPE)
			printf("Token: %s Type: PIPE Quote: %s\n", token->value, quote);
			token = token->next;
			free(quote);
		}
		printf("\n");
	}
}
