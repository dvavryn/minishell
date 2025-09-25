/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:38:28 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/23 11:50:43 by bschwarz         ###   ########.fr       */
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
	if (!new->value)
		return (free(new), NULL);
	new->quote = quote;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_token(t_data *data, t_token *new)
{
	t_token	*tmp;

	if (!new)
		ft_exit(data, "token");
	if (!data->token)
	{
		data->token = new;
		return ;
	}
	tmp = data->token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	lex_input(t_data *data)
{
	while (data->input[data->i])
	{
		while (ft_isspace(data->input[data->i]))
			data->i++;
		if (!data->input[data->i])
			break ;
		else if (data->input[data->i] == '|')
		{
			add_token(data, new_token("|", TOKEN_PIPE, QUOTE_NONE));
			data->i++;
		}
		else if (data->input[data->i] == '<' || data->input[data->i] == '>')
			add_dir_token(data);
		else
			add_word_token(data);
	}
	expand_token(data->token);
}
