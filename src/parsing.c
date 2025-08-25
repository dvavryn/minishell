/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:07:33 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/25 14:25:44 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	expand_tokens(t_token *tokens)
// {
// 	t_token	*curr;
// 	char	*expanded;

// 	curr = tokens;
// 	while (curr)
// 	{
// 		if (curr->type == TOKEN_WORD)
// 		{
// 			// expanded = expand_token_value(curr->value);
// 			free(curr->value);
// 			curr->value = expanded;
// 		}
// 		curr = curr->next;
// 	}
// }

static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	return (new);
}

static void	add_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*lex_input(char *input)
{
	t_token	*tokens = NULL;
	ssize_t	i;
	ssize_t	start;
	char	*word;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break;
		if (input[i] == '|')
		{
			add_token(&tokens, new_token("|", TOKEN_PIPE));
			i++;
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			word = read_quotes(input, &i);
			if (!word)
				return (free_tokens(&tokens), NULL);
			add_token(&tokens, new_token(word, TOKEN_WORD));
			free(word);
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) && input[i] != '|')
				i++;
			word = ft_substr(input, start, i - start);
			add_token(&tokens, new_token(word, TOKEN_WORD));
			free(word);
		}
	}
	// expand_tokens(tokens);
	return (tokens);
}
