/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:01:00 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/30 14:00:09 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_quote_token(t_data *data)
{
	char	*word;
	char	quote;
	ssize_t	start;

	quote = data->input[data->i];
	data->i++;
	start = data->i;
	while (data->input[data->i] && data->input[data->i] != quote)
		data->i++;
	if (data->input[data->i] == quote)
	{
		word = ft_substr(data->input, start, data->i - start);
		if (quote == '\'')
			add_token(data, new_token(word, TOKEN_WORD, 1));
		else if (quote == '\"')
			add_token(data, new_token(word, TOKEN_WORD, 2));
	}
	else
		ft_perror(MS E_PARS"unclosed quotes");
	data->i++;
}

void	add_word_token(t_data *data)
{
	if (data->input[data->i] == '\'' || data->input[data->i] == '\"')
		add_quote_token(data);
	else
		add_token_value(data, TOKEN_WORD);
}
