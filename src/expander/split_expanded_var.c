/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:56:53 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/28 13:58:46 by bschwarz         ###   ########.fr       */
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

static t_token	*split_tokens(t_data *data, char *value, ssize_t *i)
{
	ssize_t	start;
	t_token	*token;

	start = *i;
	token = NULL;
	if (value[*i] == '"')
	{
		while (value[++(*i)] && value[*i] != '"')
			;
		token = create_ext(data, ft_strndup(&value[start], *i - start), 0);
	}
	else if (value[*i] == '\'')
	{
		while (value[++(*i)] && value[*i] != '\'')
			;
		token = create_ext(data, ft_strndup(&value[start], *i - start), 0);
	}
	else if (value[*i] != ' ' && value[*i] != '\t')
	{
		while (value[*i] && value[*i] != ' ' && value[*i] != '\t')
			(*i)++;
		token = create_ext(data, ft_strndup(&value[start], *i - start), 0);
	}
	return (token);
}

static void	add_to_list(t_data *data, t_token *new_tokens,
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
		*ptr = new_tokens;
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

static void	split_expanded_tokens(t_data *data, t_token **prev, t_token **ptr)
{
	t_token	*new_tokens;
	t_token	*last_new;
	t_token	*token;
	ssize_t	i;

	new_tokens = NULL;
	last_new = NULL;
	i = -1;
	if (!(*ptr)->value || (*ptr)->value[0] == '\0')
		return ;
	while ((*ptr)->value[++i])
	{
		token = NULL;
		token = split_tokens(data, (*ptr)->value, &i);
		if (token)
		{
			if (!new_tokens)
				new_tokens = token;
			else
				last_new->next = token;
			last_new = token;
			i--;
		}
	}
	add_to_list(data, new_tokens, ptr, prev);
}

void	expanded_tokens(t_data *data)
{
	t_token	*ptr;
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	ptr = data->tokens;
	while (ptr)
	{
		next = ptr->next;
		if (ptr->type == TOKEN_TO_EXPAND)
			split_expanded_tokens(data, &prev, &ptr);
		else
			prev = ptr;
		ptr = ptr->next;
	}
}
