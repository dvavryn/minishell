/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:10:24 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 13:56:28 by bschwarz         ###   ########.fr       */
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

	if (!token)
		return ;
	while (token)
	{
		if (token->quote == 0)
			quote = ft_strdup("NONE");
		else if (token->quote == 1)	
			quote = ft_strdup("SINGLE");
		else if (token->quote == 2)
			quote = ft_strdup("DOUBLE");
		printf("\nToken:\t%s\n", token->value);
		if (token->type == TOKEN_WORD)
			printf("Type:\tWORD\nQuote:\t%s\n\n", quote);
		else if (token->type == TOKEN_REDIR_IN)
			printf("Type:\tRED_IN\nQuote:\t%s\n\n", quote);
		else if (token->type == TOKEN_REDIR_OUT)
			printf("Type:\tRED_OUT\nQuote:\t%s\n\n", quote);		
		else if (token->type == TOKEN_PIPE)
			printf("Type:\tPIPE\nQuote:\t%s\n\n", quote);
		token = token->next;
		free(quote);
	}
}
