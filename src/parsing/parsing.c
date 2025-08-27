/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:07:33 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 17:50:10 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int type, int quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->quote = quote;
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
			add_token(&token, new_token("|", TOKEN_PIPE, 0));
		else if (input[i] == '<')
			add_token(&token, new_token("<", TOKEN_REDIR_IN, 0));
		else if (input[i] == '>')
			add_token(&token, new_token(">", TOKEN_REDIR_OUT, 0));
		else
			token = add_word_token(token, input, &i);
		i++;
	}
	expand_token(token); //-- strcmp exe funktioniert nicht... -- values verändert???
	return (token);
}
