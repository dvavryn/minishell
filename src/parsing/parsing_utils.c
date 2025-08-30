/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:10:24 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/30 14:23:11 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token->next;
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
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
		printf("\n= = = = = = = = = =\n");
		if (token->quote == 0)
			quote = ft_strdup("NONE");
		else if (token->quote == 1)
			quote = ft_strdup("SINGLE");
		else if (token->quote == 2)
			quote = ft_strdup("DOUBLE");
		if (token->type == TOKEN_WORD)
			printf("TYPE:\t WORD\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",token->value, quote);
		else if (token->type == TOKEN_REDIR_IN)
			printf("TYPE:\t RED_IN\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",token->value, quote);
		else if (token->type == TOKEN_REDIR_OUT)
			printf("TYPE:\t RED_OUT\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",token->value, quote);
		else if (token->type == TOKEN_PIPE)
			printf("TYPE:\t PIPE\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",token->value, quote);
		else if (token->type == TOKEN_HEREDOC)
			printf("TYPE:\t HEREDOC\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",token->value, quote);
		else if (token->type == TOKEN_APPEND_OUT)
			printf("TYPE:\t APPEND_OUT\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",token->value, quote);
		printf("= = = = = = = = = =\n\n");
		token = token->next;
		free(quote);
	}
}
