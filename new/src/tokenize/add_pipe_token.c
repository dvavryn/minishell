/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:00 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:45:08 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

void	add_pipe_token(t_data *data)
{
	t_token	*to_add;

	to_add = new_token("|", TOKEN_PIPE, QUOTE_NONE);
	if (!to_add)
		ft_exit(data, MAL_ERR, 1);
	add_token(data, to_add);
}
