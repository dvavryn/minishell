/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:42:31 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/26 13:05:20 by bschwarz         ###   ########.fr       */
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

static t_token	*skip_redir(t_token *ptr, t_token **prev)
{
	if (ptr && ptr->next && ptr->next->next)
	{
		*prev = ptr->next;
		return (ptr->next->next);
	}
	*prev = ptr;
	return (NULL);
}

static t_token	*handle_expansion(t_data *data, t_token *ptr, t_token **prev)
{
	split_expanded_tokens(data, prev, &ptr);
	if (*prev == NULL)
		return (data->tokens);
	return ((*prev)->next);
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
			ptr = skip_redir(ptr, &prev);
		else if (ptr->expanded == 1)
			ptr = handle_expansion(data, ptr, &prev);
		else
		{
			prev = ptr;
			ptr = next;
		}
	}
}
