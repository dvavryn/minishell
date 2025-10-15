/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:42:31 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 20:43:31 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_expanded_tokens(t_data *data, t_token **prev, t_token **ptr)
{
	t_token	*new_tokens;
	t_token	*last_new;
	t_token	*token;
	ssize_t	i;

	new_tokens = NULL;
	last_new = NULL;
	i = 0;
	if (!(*ptr)->value || (*ptr)->value[0] == '\0')
		return ;
	while ((*ptr)->value[i])
	{
		token = split_tokens(data, (*ptr)->value, &i);
		if (token)
		{
			if (!new_tokens)
				new_tokens = token;
			else
				last_new->next = token;
			last_new = token;
		}
	}
	add_to_list(data, new_tokens, ptr, prev);
}

void	expanded_tokens(t_data *data)
{
	t_token	*ptr;
	t_token	*prev;

	prev = NULL;
	ptr = data->tokens;
	while (ptr)
	{
		if (ptr->type == TOKEN_REDIR || ptr->type == TOKEN_HEREDOC)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		if (ptr->expanded == 1)
			split_expanded_tokens(data, &prev, &ptr);
		else
			prev = ptr;
		if (ptr)
			ptr = ptr->next;
	}
}
