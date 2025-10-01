/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:56:53 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/01 13:49:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static t_token	*create_extended_token(t_data *data, char *value, int type)
// {
// 	t_token	*new;

// 	new = ft_calloc(1, sizeof(t_token));
// 	if (!new)
// 		ft_exit(data, "malloc");
// 	new->value = value;
// 	new->type = type;
// 	return (new);
// }

// static void	split_expanded_tokens(t_data *data, t_token **prev, t_token **curr)
// {
// 	t_token	*new;
// 	t_token	*last_new;
// 	t_token	*next;
// 	char	*value;
// 	ssize_t	i;
// 	ssize_t	start;

// 	value = (*curr)->value;
// 	new = NULL;
// 	last_new = NULL;
// 	i = -1;
// 	while (value[++i])
// 	{
// 		start = i;
// 		if (value[i] == '\"')
// 		{
// 			while (value[++i] && value[i] != '\"')
// 				;
// 			token = create_extended_token(data, ptr, ft_strndup(&value[start], i - start TOKEN_WORD));
// 		}
// 		else if (value[i] == '\'')
// 		{
// 			while (value[++i] && value[i] != '\'')
// 				;
// 			token = create_extended_token(data, ptr, ft_strndup(&value[start], i - start TOKEN_WORD));
// 		}
// 		else if (value[i] != ' ' && value[i] != '\t')
// 		{
// 			while (value[i] && value[i] != ' ' && value[i] != '\t')
// 				i++;
// 			token = create_extended_token(data, ptr, ft_strndup(&value[start], i - start TOKEN_WORD));
// 		}
// 		ptr = ptr->next;
// 	}
// }

// void	expanded_tokens(t_data *data)
// {
// 	t_token	*ptr;
// 	t_token	*prev;
// 	t_token	*next;

// 	prev = NULL;
// 	ptr = data->tokens;
// 	while (ptr)
// 	{
// 		next = ptr->next;
// 		if (ptr->type == TOKEN_TO_EXPAND)
// 			split_expanded_tokens(data, &prev, &ptr);
// 		else
// 			prev = ptr;
// 		ptr = next;
// 	}
// }
