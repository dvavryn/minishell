/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:48:29 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 15:02:06 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_sub(t_data *data, char *ptr, size_t *i)
{
	char	*var;
	char	c;
	char	*out;

	c = ptr[*i];
	ptr[*i] = 0;
	var = ft_strdup(&ptr[1]);
	ptr[*i] = c;
	if (!var)
		return (NULL);
	if (!ms_getenv(data->env, var))
		out = ft_strdup("");
	else
		out = ft_strdup(ms_getenv(data->env, var));
	free(var);
	if (!out)
		return (NULL);
	return (out);
}

static char	*expand_heredoc_first(char *ptr, char *out, size_t *i)
{
	char	*buf[2];

	(*i) = 0;
	while (ptr[*i] && ptr[*i] != '$')
		(*i)++;
	buf[0] = ft_substr(ptr, 0, *i);
	if (!buf[0])
		return (free(out), NULL);
	buf[1] = out;
	out = ft_strjoin(out, buf[0]);
	free(buf[0]);
	free(buf[1]);
	if (!out)
		return (NULL);
	return (out);
}

static char	*expand_heredoc_last(t_data *data, char *ptr, char *out, size_t *i)
{
	char	*buf[2];

	(*i) = 1;
	while (ptr[*i] && ft_isalnum(ptr[*i]))
		(*i)++;
	buf[0] = expand_heredoc_sub(data, ptr, &(*i));
	if (!buf[0])
		return (free(out), NULL);
	buf[1] = out;
	out = ft_strjoin(out, buf[0]);
	free(buf[0]);
	free(buf[1]);
	if (!out)
		return (NULL);
	return (out);
}

char	*expand_heredoc(t_data *data, char *ptr)
{
	char	*out;
	size_t	i;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (*ptr)
	{
		out = expand_heredoc_first(ptr, out, &i);
		if (!out)
			return (NULL);
		ptr += i;
		if (*ptr == '$')
		{
			out = expand_heredoc_last(data, ptr, out, &i);
			if (!out)
				return (NULL);
			ptr += i;
		}
	}
	return (out);
}
