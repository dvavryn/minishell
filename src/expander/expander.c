/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:50:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 19:48:58 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(t_data *data, char *ptr, size_t *i)
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

static int	expand_word_skip(char *ptr, int flag)
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

static char	*expand_word_dquote(int *flag, char **in)
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

static int	expander_sub(t_data *data, t_expand *exp)
{
	if (*exp->ptr == '\"')
	{
		exp->out = expand_word_dquote(&exp->flag, &exp->out);
		if (!exp->out)
			return (0);
		exp->ptr++;
	}
	if (*exp->ptr == '$')
	{
		exp->i = 1;
		while (exp->ptr[exp->i] && ft_isalnum(exp->ptr[exp->i]))
			exp->i++;
		if (exp->i == 1 && exp->ptr[exp->i] == '?')
		{
			exp->i++;
			exp->buf1 = ft_itoa(data->last_ret);
		}
		else
			exp->buf1 = expand_var(data, exp->ptr, &exp->i);
		if (!exp->buf1)
			return (free(exp->out), 0);
		exp->buf2 = exp->out;
		exp->out = ft_strjoin(exp->out, exp->buf1);
		free(exp->buf1);
		free(exp->buf2);
		if (!exp->out)
			return (0);
		exp->ptr += exp->i;
	}
	return (1);
}

static void	init_exp(t_expand *exp, char *input)
{
	ft_bzero(exp, sizeof(t_expand));
	exp->ptr = input;
	exp->out = ft_strdup("");
	if (!exp->out)
		exp->out = NULL;
}

static char	*expand_word(t_data *data, char *input)
{
	t_expand	exp;

	init_exp(&exp, input);
	if (!exp.out)
		return (NULL);
	while (*exp.ptr)
	{
		exp.i = expand_word_skip(exp.ptr, exp.flag);
		exp.buf1 = ft_substr(exp.ptr, 0, exp.i);
		if (!exp.buf1)
			return (free(exp.out), NULL);
		exp.buf2 = exp.out;
		exp.out = ft_strjoin(exp.out, exp.buf1);
		free(exp.buf1);
		free(exp.buf2);
		if (!exp.out)
			return (NULL);
		exp.ptr += exp.i;
		if (!expander_sub(data, &exp))
			return (NULL);
	}
	return (exp.out);
}

void	expander(t_data *data)
{
	t_token	*ptr;
	char	*buf;

	ptr = data->tokens;
	while (ptr)
	{
		if (ptr->type == TOKEN_HEREDOC)
			ptr = ptr->next;
		else if (ptr->type == TOKEN_REDIR || ptr->type == TOKEN_PIPE)
			;
		else if (ft_strchr(ptr->value, '$'))
		{
			buf = expand_word(data, ptr->value);
			if (!buf)
				ft_exit(data, "malloc");
			free(ptr->value);
			ptr->expanded = 1;
			ptr->value = buf;
		}
		ptr = ptr->next;
	}
}
