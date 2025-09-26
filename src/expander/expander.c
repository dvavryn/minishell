/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:50:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 15:16:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(t_data *data, char *s, size_t *pos)
{
	char	*out;
	char	*tmp;
	char	*var;
	size_t	i;

	i = 0;
	while (s[++i] && ft_isalnum(s[i]))
		;
	tmp = ft_strndup(s, i);
	if (!tmp)
		return (NULL);
	var = ms_getenv(data->env, tmp + 1);
	if (!var)
		out = ft_strdup("");
	else
		out = ft_strdup(var);
	free(tmp);
	if (!out)
		return (NULL);
	*pos += i; 
	return (out);
}

static char	*expand_double(t_data *data, char *ptr, size_t *i)
{
	char	*out;
	char	*buf;
	char	*tmp;
	size_t	j;
	
	out = ft_strdup("");
	if (!out)
		return (NULL);
	tmp = ptr;
	while (*tmp && *tmp != '"')
	{
		j = 0;
		while (tmp[j] && tmp[j] != '"' && tmp[j] != '$')
			j++;
		buf = out;
		out = ft_strjoin(out, expand_var(data, tmp, &j));
		free(out);
		if (!out)
			return (NULL);
		tmp += j;
		*i += j;
	}
	return (out);
}

static void	skip_single(char *ptr, size_t *i)
{
	while (ptr[*i] && ptr[*i] != '\'')
		(*i)++;
}

static int	expand_word(t_data * data, t_token *token)
{
	char	*ptr;
	char	*out;
	char	*buf;
	size_t	i;

	ptr = token->value;
	out = ft_strdup("");
	if (!out)
		return (0);
	while (*ptr)
	{
		i = 0;
		while (ptr[i] && ptr[i] != '\'' && ptr[i] != '"' && ptr[i] != '$')
			i++;
		out = ft_strjoin(out, ft_strndup(ptr, i));
		if (!out)
			return (0);
		if (!ptr)	// ????????????
			break ;	// ????????????
		ptr += i;
		i = 1;
		if (ptr[i - 1] == '\'')
		{
			skip_single(ptr, &i);
			buf = out;
			out = ft_strjoin(out, ft_strndup(ptr, i));
			free(buf);
			if (!out)
				return (0);
		}
		else if (ptr[i - 1] == '"')
		{
			buf = out;
			out = ft_strjoin(out, "\"");
			free(buf);
			if (!out)
				return (0);
			buf = out;
			out = ft_strjoin(out, expand_double(data, ptr, &i));
			free(buf);
			if (!out)
				return (0);
			buf = out;
			out = ft_strjoin(out, "\"");
			free(buf);
			if (!out)
				return (0);
		}
		else if (ptr[i - 1] == '$')
		{
			buf = out;
			out = expand_var(data, ptr, &i);
			free(buf);
			if (!out)
				return (0);
		}
		ptr += i;
	}
	free(token->value);	// ??????
	token->value = out;	// ??????
	return (1);
}

void	expander(t_data *data)
{
	t_token *ptr;

	ptr = data->tokens;
	while (ptr)
	{
		
		if (ptr->type == TOKEN_HEREDOC)
			ptr = ptr->next;
		else if (ptr->type == TOKEN_REDIR || ptr->type == TOKEN_PIPE)
			;
		else
		{
			if (expand_word(data, ptr)
				&& (ft_strchr(ptr->value, '"') || ft_strchr(ptr->value, '$')))
				ft_exit(data, "malloc");
		}
		ptr = ptr->next;
	}
}
