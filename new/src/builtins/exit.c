/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:43:12 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:44:38 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_data *data)
{
	t_token	*ptr;
	int		ret;

	ret = 0;
	ptr = data->token;
	if (data->token && data->token->type == TOKEN_WORD
		&& !ft_strcmp(data->token->value, "exit"))
	{
		printf("%s\n", data->token->value);
		if (data->token->next && data->token->next->type == TOKEN_WORD)
			ret = ft_atoi(data->token->next->value);
		ft_exit(data, ret, 0);
	}
}
