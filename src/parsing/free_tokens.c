/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:10:24 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/26 15:05:16 by bschwarz         ###   ########.fr       */
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
	while (token)
	{
		if (token->type == TOKEN_WORD)
			printf("Token: %s Type: WORD\n", token->value);
		else if (token->type == TOKEN_REDIR_IN)
			printf("Token: %s Type: RED_IN\n", token->value);
		else if (token->type == TOKEN_REDIR_OUT)
			printf("Token: %s Type: RED_OUT\n", token->value);		
		else if (token->type == TOKEN_PIPE)
			printf("Token: %s Type: PIPE\n", token->value);
		token = token->next;
	}
}
