/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:17 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/04 14:32:12 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

int	tokenize(t_data *data)
{
	data->token = NULL;
	while (data->input[data->i])
	{
		while (ft_isspace(data->input[data->i]))
			data->i++;
		if (!data->input[data->i])
			break ;
		else if (data->input[data->i] == '|')
			add_pipe_token(data);
		else if (data->input[data->i] == '<' || data->input[data->i] == '>')
			add_redir_token(data);
		else
		{
			if (add_word_token(data))
			{
				write(2, "UNCLOSED QUOTES??\n", 18);
				return (1);
			}
		}
	}
	return (0);
}

void	free_token(t_token	*token)
{
	t_token	*ptr;

	if (!token)
		return ;
	while (token)
	{
		if (token)
		{
			ptr = token->next;
			if (token->value)
				free(token->value);
			token->value = NULL;
		}
		free(token);
		token = ptr;
	}
	token = NULL;
}
