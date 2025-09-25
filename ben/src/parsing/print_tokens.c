/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:40:25 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/01 14:42:06 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_printing_quote(t_token *token)
{
	char	*quote;

	quote = NULL;
	if (token->quote == QUOTE_NONE)
		quote = ft_strdup("NONE");
	else if (token->quote == QUOTE_SINGLE)
		quote = ft_strdup("SINGLE");
	else if (token->quote == QUOTE_DOUBLE)
		quote = ft_strdup("DOUBLE");
	else if (token->quote == QUOTE_HD)
		quote = ft_strdup("HD");
	return (quote);
}

static char	*get_printing_type(t_token *token)
{
	char	*type;

	type = NULL;
	if (token->type == TOKEN_WORD)
		type = ft_strdup("WORD");
	else if (token->type == TOKEN_PIPE)
		type = ft_strdup("PIPE");
	else if (token->type == TOKEN_REDIR_IN)
		type = ft_strdup("RED_IN");
	else if (token->type == TOKEN_REDIR_OUT)
		type = ft_strdup("RED_OUT");
	else if (token->type == TOKEN_HEREDOC)
		type = ft_strdup("HEREDOC");
	else if (token->type == TOKEN_APPEND_OUT)
		type = ft_strdup("APPEND_OUT");
	return (type);
}

void	print_tokens(t_token *token)
{
	char	*quote;
	char	*type;

	if (!token)
		return ;
	while (token)
	{
		printf("\n= = = = = = = = = =\n");
		quote = get_printing_quote(token);
		type = get_printing_type(token);
		printf("TYPE:\t %s\nVALUE:\t\"%s\"\nQUOTE:\t %s\n",
			type, token->value, quote);
		printf("= = = = = = = = = =\n\n");
		token = token->next;
		free(quote);
	}
}
