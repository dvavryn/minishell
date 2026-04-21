/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:37 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 17:15:46 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*ptr;

	while (tokens)
	{
		ptr = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = ptr;
	}
}
