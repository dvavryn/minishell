/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:07:33 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/25 17:21:58 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	expand_token(t_token *token)
// {
// 	t_token	*curr;
// 	char	*expanded;

// 	curr = token;
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

t_token	*new_token(char *value, t_token_type type)
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

void	add_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
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
	t_token	*token = NULL;
	ssize_t	i;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		else if (input[i] == '|')
			add_token(&token, new_token("|", TOKEN_PIPE));
		else if (input[i] == '<')
			add_token(&token, new_token("<", TOKEN_REDIR_IN));
		else if (input[i] == '>')
			add_token(&token, new_token(">", TOKEN_REDIR_OUT));
		else
			token = add_word_token(token, input, &i);
		i++;
	}
	// expand_token(token);
	return (token);
}
