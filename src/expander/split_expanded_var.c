/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:56:53 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/15 20:44:54 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_ext(t_data *data, char *value, int type)
{
	t_token	*new;

	if (!value)
		ft_exit(data, "malloc");
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_exit(data, "malloc");
	new->value = value;
	new->type = type;
	return (new);
}

static t_token	*handle_quotes(t_data *data, char *value, ssize_t *i)
{
	ssize_t	start;
	char	quote;

	quote = value[*i];
	start = *i;
	(*i)++;
	while (value[*i] && value[*i] != quote)
		(*i)++;
	if (value[*i] == quote)
		(*i)++;
	return (create_ext(data, ft_strndup(&value[start], *i - start), 1));
}

static t_token	*handle_word(t_data *data, char *value, ssize_t *i)
{
	ssize_t	start;

	start = *i;
	while (value[*i] && value[*i] != ' ' && value[*i] != '\t'
		&& value[*i] != '"' && value[*i] != '\'')
		(*i)++;
	if (*i - start == 0)
		return (NULL);
	return (create_ext(data, ft_strndup(&value[start], *i - start), 1));
}

t_token	*split_tokens(t_data *data, char *value, ssize_t *i)
{
	t_token	*token;

	token = NULL;
	if (value[*i] == ' ' || value[*i] == '\t')
		(*i)++;
	if (!value[*i])
		return (NULL);
	if (value[*i] == '"' || value[*i] == '\'')
		token = handle_quotes(data, value, i);
	else
		token = handle_word(data, value, i);
	return (token);
}

void	add_to_list(t_data *data, t_token *new_tokens,
		t_token **ptr, t_token **prev)
{
	t_token	*next;
	t_token	*tmp;

	next = (*ptr)->next;
	free((*ptr)->value);
	free(*ptr);
	if (new_tokens)
	{
		if (*prev)
			(*prev)->next = new_tokens;
		else
			data->tokens = new_tokens;
		tmp = ms_lstlast(new_tokens);
		tmp->next = next;
		*ptr = tmp;
	}
	else
	{
		if (*prev)
			(*prev)->next = next;
		else
			data->tokens = next;
		*ptr = next;
	}
}
