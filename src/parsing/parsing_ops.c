/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:47:58 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/26 15:58:56 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_word_token(t_token *token, char *input, ssize_t *i)
{
	char	*word;
	ssize_t	start;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		word = read_quotes(input, i);
		if (!word)
			return (free_tokens(token), NULL);
		add_token(&token, new_token(word, TOKEN_WORD));
		free(word);
	}
	else
	{
		start = *i;
		while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|')
			(*i)++;
		word = ft_substr(input, start, (long)(*i) - start);
		add_token(&token, new_token(word, TOKEN_WORD));
		free(word);
	}
	return (token);
}

char	*read_quotes(char *input, ssize_t *i)
{
	int		start;
	char	quote;
	char	*word;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		ft_perror(MS E_PARS"unclosed quotes");
		return (NULL);
	}
	word = ft_strndup(&input[start], *i - start);
	if (input[*i] == quote)
		(*i)++;
	return (word);
}
