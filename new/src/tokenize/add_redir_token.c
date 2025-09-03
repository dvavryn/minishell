/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:03 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:15:32 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

void	add_redir_token(t_data *data)
{
	if (data->input[data->i] == '<' && data->input[data->i + 1] == '<')
	{
		data->i += 2;
		add_token_value(data, TOKEN_HEREDOC);
		// clean_heredoc_token(data);
	}
	else if (data->input[data->i] == '>' && data->input[data->i + 1] == '>')
	{
		data->i += 2;
		add_token_value(data, TOKEN_APPEND_OUT);
	}
	else if (data->input[data->i] == '<')
	{
		data->i++;
		add_token_value(data, TOKEN_REDIR_IN);
	}
	else if (data->input[data->i] == '>')
	{
		data->i++;
		add_token_value(data, TOKEN_REDIR_OUT);
	}
}
