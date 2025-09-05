/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:15:50 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 14:35:57 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_getenv(t_data *data, char *name)
{
	char	*out;
	ssize_t	i;

	out = ft_strjoin(name, "=");
	if (!out)
		return (NULL);
	i = -1;
	while (data->envp[++i])		
		if (!ft_strncmp(data->envp[i], out, ft_strlen(out)))
			break ;
	free(out);
	out = NULL;
	if (!data->envp[i])
		out = ft_strdup("");
	else
		out = ft_strdup(data->envp[i] + ft_strlen(name) + 1);
	if (!out)
		return (NULL);
	return (out);
}

static char	*get_var_name(t_data *data, const char *value, ssize_t *i)
{
	ssize_t	start;
	char	*tmp;
	char	*result;

	if (value[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->last_return_value));
	}
	if (!ft_isalpha(value[*i]) && value[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalpha(value[*i]) || value[*i] == '_')
		(*i)++;
	tmp = ft_substr(value, start, *i - start);
	if (!tmp)
		return (ft_strdup(""));
	result = ms_getenv(data, tmp); //change to our envirement
	free(tmp);
	if (!result)
		return (ft_strdup(""));
	return (result);
}

static void	expand_word_sub(t_data *data, t_token *token, char **out, ssize_t *i)
{
	if (token->value[*i] == '$')
	{
		(*i)++;
		out[0] = get_var_name(data, token->value, i);
		if (!out[0])
			ft_exit(data, MAL_ERR, MAL_ERR);
		out[2] = out[1];
		out[1] = ft_strjoin(out[1], out[0]);
		free(out[0]);
		(*i)--;				
	}
	else
	{
		out[2] = out[1];
		out[1] = ft_strjoinc(out[1], token->value[*i]);		
	}
	free(out[2]);
	if (!out[1])
		ft_exit(data, MAL_ERR, MAL_ERR);
}

static void	expand_word(t_data *data, t_token *token)
{
	ssize_t	i;
	char	*out[3];

	i = -1;
	out[1] = ft_strdup("");
	if (!out[1])
		ft_exit(data, MAL_ERR, MAL_ERR);
	while (token->value[++i])
		expand_word_sub(data, token, out, &i);
	free(token->value);
	token->value = out[1];
}

void	expander(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	while (ptr)
	{
		if (ptr->value && ft_strchr(ptr->value, '$')
			&& ptr->type == TOKEN_WORD && ptr->quote != QUOTE_SINGLE)
			expand_word(data, ptr);
		ptr = ptr->next;
	}
}
