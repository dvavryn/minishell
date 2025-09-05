/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:29:03 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 13:34:54 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*cleanup_token_sub(char *value)
{
	char	*out;
	char	*tmp;
	ssize_t	i;

	i = -1;
	out = ft_strdup("");
	while (value[++i])
	{
		if (!(value[i] == '\'' || value[i] == '\"'))
		{
			tmp = out;
			out = ft_strjoinc(out, value[i]);
			free(tmp);
			if (!out)
				return (NULL);
		}
	}
	free(value);
	return (out);
}

void	cleanup_token(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	while (ptr)
	{
		if (ft_strchr(ptr->value, '\'') || ft_strchr(ptr->value, '\"'))
		{
			ptr->value = cleanup_token_sub(ptr->value);
			if (!ptr->value)
				ft_exit(data, MAL_ERR, MAL_ERR);
		}
		ptr = ptr->next;
	}
}