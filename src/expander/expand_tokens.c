/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:42:31 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/24 15:00:36 by bschwarz         ###   ########.fr       */
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
	t_token	*next;

	prev = NULL;
	ptr = data->tokens;
	while (ptr)
	{
		next = ptr->next;
		if (ptr->type == TOKEN_REDIR || ptr->type == TOKEN_HEREDOC)
		{
			if (ptr->next)
				ptr = ptr->next->next;
			ptr = ptr->next;
			continue ;
		}
		if (ptr->expanded == 1)
		{
			split_expanded_tokens(data, &prev, &ptr);
			continue ;
		}
		else
			prev = ptr;
		ptr = next;
	}
}
