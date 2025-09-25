/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:11:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 17:11:38 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cleanup_args_sub3(char *s, size_t *i)
{
	size_t	j;
	char	*out;

	j = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '\"')
		(*i)++;
	out = ft_substr(s, j, *i - j);
	if (!out)
		return (NULL);
	return (out);
}

static char	*cleanup_args_sub2(char *s, size_t *i)
{
	size_t	j;
	char	c;
	char	*out;

	c = s[(*i)++];
	j = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] == c)
	{
		out = ft_substr(s, j, *i - j);
		(*i)++;
	}
	else
	{
		out = ft_substr(s, j - 1, ft_strlen(s) - j - 1);
		*i = ft_strlen(s);
	}
	if (!out)
		return (NULL);
	return (out);
}

static char	*cleanup_args_sub(char *s)
{
	size_t	i;
	char	*out;
	char	*buf[2];

	i = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			buf[0] = cleanup_args_sub2(s, &i);
		else
			buf[0] = cleanup_args_sub3(s, &i);
		if (!buf[0])
			return (free(out), NULL);
		buf[1] = out;
		out = ft_strjoin(out, buf[0]);
		free(buf[0]);
		free(buf[1]);
		if (!out)
			return (NULL);
	}
	return (out);
}

void	cleanup_args(t_data *data)
{
	t_cmd	*ptr;
	ssize_t	i;
	char	*buf;

	ptr = data->cmd;
	while (ptr)
	{
		if (ptr->args)
		{
			i = -1;
			while (ptr->args[++i])
			{
				buf = cleanup_args_sub(ptr->args[i]);
				if (!buf)
					ft_exit(data, "malloc");
				free(ptr->args[i]);
				ptr->args[i] = buf;
			}
		}
		ptr = ptr->next;
	}
}
