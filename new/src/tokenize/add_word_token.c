/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/04 14:24:12 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static void	add_quote_token_sub(t_data *data, char *value, int quote)
{
	t_token	*to_add;

	to_add = new_token(value, TOKEN_WORD, quote);
	free(value);
	if (!to_add)
		ft_exit(data, MAL_ERR, 1);
	add_token(data, to_add);
}

static int	add_quote_token(t_data *data)
{
	char	*value;
	char	quote;
	size_t	start;

	quote = data->input[data->i];
	data->i++;
	start = data->i;
	while (data->input[data->i] && data->input[data->i] != quote)
		data->i++;
	if (data->input[data->i] == quote)
	{
		value = ft_substr(data->input, start, data->i - start);
		if (!value)
			ft_exit(data, MAL_ERR, 1);
		if (quote == '\'')
			add_quote_token_sub(data, value, QUOTE_SINGLE);
		else if (quote == '\"')
			add_quote_token_sub(data, value, QUOTE_DOUBLE);
		return (0);
	}
	else
		return (1);
}

int	add_word_token(t_data *data)
{
	if (data->input[data->i] == '\'' || data->input[data->i] == '\"')
	{
		if (add_quote_token(data))
			return (1);
		data->i++;
	}
	else
		add_token_value(data, TOKEN_WORD);
	return (0);
}
