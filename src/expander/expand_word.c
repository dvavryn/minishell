/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:19:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 21:25:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_word_skip(char *ptr, int flag)

{
	size_t	i;

	i = 0;
	if (!flag)
	{
		while (ptr[i] && !ft_strchr("$\'\"", ptr[i]))
			i++;
		if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i] && ptr[i] != '\'')
				i++;
			i++;
		}
	}
	else
	{
		while (ptr[i] && !ft_strchr("$\"", ptr[i]))
			i++;
	}
	return (i);
}

char	*expand_word_dquote(int *flag, char **in)
{
	char	*out;

	if (!*flag)
		*flag = 1;
	else
		*flag = 0;
	out = ft_strjoin(*in, "\"");
	free(*in);
	if (!out)
		return (NULL);
	return (out);
}

void	init_exp(t_expand *exp, char *input)
{
	ft_bzero(exp, sizeof(t_expand));
	exp->ptr = input;
	exp->out = ft_strdup("");
	if (!exp->out)
		exp->out = NULL;
}
