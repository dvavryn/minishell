/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:50:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 15:58:07 by dvavryn          ###   ########.fr       */
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

static char	*expand_word(t_data *data, char *input)
{
	char	*out;
	char	*buf[2];
	char	*ptr;
	size_t	i;
	
	ptr = input;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (*ptr)
	{
		i = 0;
		while (ptr[i] && ptr[i] != '$' && ptr[i] == '"' && ptr[i] != '\'')
			i++;
		if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i])
				i++;
			i++;
		}
		buf[0] = ft_substr(ptr, 0, i);
		if (!buf[0])
			return (free(out), NULL);
		buf[1] = out;
		out = ft_strjoin(out, buf[0]);
		free(buf[0]);
		free(buf[1]);
		if (!out)
			return (NULL);
		ptr += i;
		if (*ptr == '$')
		{
			i = 1;
			while (ptr[i] && ft_isalnum(ptr[i]))
				i++;
			buf[0] = expand_var(data, ptr, &i);
			if (!buf[0])
				return (free(out), NULL);
			buf[1] = out;
			out = ft_strjoin(out, buf[0]);
			free(buf[0]);
			free(buf[1]);
			if (!out)
				return (NULL);
			ptr += i;
		}
	}
	return (out);
}

void	expander(t_data *data)
{
	t_token *ptr;
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
			ptr->value = buf;
		}
		ptr = ptr->next;
		
	}
}
