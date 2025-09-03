/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:34:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:45:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static void	add_token_value_sub(t_data *data, char *value, int type, int quote)
{
	t_token	*to_add;

	to_add = new_token(value, type, quote);
	free(value);
	if (!to_add)
		ft_exit(data, MAL_ERR, 1);
	add_token(data, to_add);
}

static int	ft_isspecial(int c)
{
	return ((c == '|' || c == '<' || c == '>'));
}

static int	check_heredoc_quote(char *value)
{
	ssize_t	i;

	i = -1;
	while (value[++i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			return (1);
	}
	return (0);
}

void	add_token_value(t_data *data, int type)
{
	char	*value;
	size_t	start;

	while (ft_isspace(data->input[data->i]))
		data->i++;
	start = data->i;
	while (data->input[data->i] && !ft_isspace(data->input[data->i])
		&& !ft_isspecial(data->input[data->i]))
		data->i++;
	value = ft_substr(data->input, start, data->i - start);
	if (!value)
		ft_exit(data, MAL_ERR, 1);
	if (type == TOKEN_HEREDOC && check_heredoc_quote(value))
		add_token_value_sub(data, value, type, QUOTE_HD);
	else
		add_token_value_sub(data, value, type, QUOTE_NONE);
}
