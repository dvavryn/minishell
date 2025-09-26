/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:33:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 15:34:21 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_token(ssize_t len, char *value, int type)
{
	t_token	*out;

	out = ft_calloc(1, sizeof(t_token));
	if (!out)
		return (NULL);
	out->value = ft_strndup(value, len);
	if (!out->value)
	{
		free(out);
		return (NULL);
	}
	out->type = type;
	return (out);
}

static void	add_token(t_data *data, ssize_t len, char *value, int type)
{
	t_token	*ptr;

	ptr = data->tokens;
	if (!data->tokens)
	{
		data->tokens = new_token(len, value, type);
		if (!data->tokens)
			ft_exit(data, "malloc");
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_token(len, value, type);
		if (!ptr->next)
			ft_exit(data, "malloc");
	}
}

void	add_token_pipe(t_data *data)
{
	add_token(data, 1, &data->input[data->i], TOKEN_PIPE);
	data->i++;
}

void	add_token_redir(t_data *data)
{
	int		c;
	size_t	len;

	c = data->input[data->i];
	len = 1;
	if (data->input[data->i] == data->input[data->i + 1])
	{
		len++;
		if (c == '<')
			add_token(data, len, &data->input[data->i], TOKEN_HEREDOC);
		else
			add_token(data, len, &data->input[data->i], TOKEN_REDIR);
	}
	else
		add_token(data, len, &data->input[data->i], TOKEN_REDIR);
	data->i += len;
}

void	add_token_word(t_data *data)
{
	ssize_t	start;
	int		type;
	int		c;

	start = data->i;
	while (data->input[data->i] && !ft_strchr(" \t|<>", data->input[data->i]))
	{
		if (ft_strchr("'\"", data->input[data->i]))
		{
			c = data->input[data->i];
			data->i++;
			while (data->input[data->i] && data->input[data->i] != c)
				data->i++;
		}
		if (data->input[data->i])
			data->i++;
	}
	if (ft_strchr("'\"", data->input[start]))
		type = TOKEN_QUOTE;
	else if (data->input[start] == '$')
		type = TOKEN_TO_EXPAND;
	else
		type = TOKEN_WORD;
	if (data->i - start != 0)
		add_token(data, data->i - start, &data->input[start], type);
}
