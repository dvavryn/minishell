/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:09 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 15:35:10 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token	*new_token(char	*value, int type, int quote)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->quote = quote;
	new->type = type;
	return (new);
}

void	add_token(t_data *data, t_token *to_add)
{
	t_token	*tmp;

	if (!data->token)
		data->token = to_add;
	else
	{
		tmp = data->token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = to_add;
	}
}
