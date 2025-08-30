/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:59:47 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/30 14:11:25 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_heredoc_token(t_data *data)
{
	char	*src;
	char	*dst;
	t_token	*last;
	ssize_t	j;
	ssize_t	k;

	if (!data->token)
		return ;
	last = data->token;
	while (last->next)
		last = last->next;
	if (last->type != TOKEN_HEREDOC || !last->value)
		return ;
	src = last->value;
	dst = last->value;
	j = -1;
	k = 0;
	while (src[++j])
		if (src[j] != '\'' && src[j] != '\"')
			dst[k++] = src[j];
	dst[k] = '\0';
}

void	add_token_value(t_data *data, int type)
{
	char	*word;
	ssize_t	start;

	while (ft_isspace(data->input[data->i]))
		data->i++;
	start = data->i;
	while (data->input[data->i] && !ft_isspace(data->input[data->i])
		&& data->input[data->i] != '|' && data->input[data->i] != '<'
		&& data->input[data->i] != '>' )
		data->i++;
	word = ft_substr(data->input, start, data->i - start);
	add_token(data, new_token(word, type, 0));
}

static void	handle_input_redir(t_data *data)
{
	if (data->input[data->i + 1] == '<')
	{
		data->i += 2;
		add_token_value(data, TOKEN_HEREDOC);
		if (data->token)
			clean_heredoc_token(data);
	}
	else
	{
		data->i++;
		add_token_value(data, TOKEN_REDIR_IN);
	}
}

static void	handle_output_redir(t_data *data)
{
	if (data->input[data->i + 1] == '>')
	{
		data->i += 2;
		add_token_value(data, TOKEN_APPEND_OUT);
	}
	else
	{
		data->i++;
		add_token_value(data, TOKEN_REDIR_OUT);
	}
}

void	add_dir_token(t_data *data)
{
	if (data->input[data->i] == '<')
		handle_input_redir(data);
	else if (data->input[data->i] == '>')
		handle_output_redir(data);
}
