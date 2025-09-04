/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:15:50 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/04 16:05:39 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char *join(char *in, char *value, size_t len)
// {
// 	char *out;
// 	char *tmp;

// 	tmp = ft_substr(value, 0, len);
// 	if (!tmp)
// 	{
// 		free(in);
// 		return (NULL);
// 	}
// 	if (!in)
// 		out = ft_strjoin("", tmp);
// 	else
// 		out = ft_strjoin("")
	
// }

static void	expand_word(t_data *data, char *value)
{
	ssize_t	i;
	ssize_t	j;
	char *tmp;
	char *buf;
	
	(void)data;

	i = -1;
	buf = NULL;
	while (value[++i])
	{
		j = -1;
		if (value[i] == '$')
			j++;
		while (value[++j + i] && value[j + i] != '$')
			;
		buf = ft_substr(&value[i], 0, j);
		if (!buf)
			ft_exit(data, MAL_ERR, MAL_ERR);
		printf("%s\n", buf);
		i += j - 1;
	}
}

void	expander(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	while (ptr)
	{
		if (ptr->value && ft_strchr(ptr->value, '$') && ptr->type == TOKEN_WORD && ptr->quote != QUOTE_SINGLE)
		{
			expand_word(data, ptr->value);
			// printf("%s\n", ptr->value);
		}
		ptr = ptr->next;
	}
}