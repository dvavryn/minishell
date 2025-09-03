/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:05:50 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:52:05 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_charjoin(char const *s1, char const c)
{
	char	*dest;
	int		i;

	if (!s1 || !c)
		return (NULL);
	dest = malloc((ft_strlen((char *)s1)
				+ 2) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	dest[i] = c;
	dest[++i] = '\0';
	return (dest);
}

static char	*get_var_name(const char *value, ssize_t *i)
{
	ssize_t	start;
	char	*tmp;
	char	*result;

	if (value[*i] == '?' || value[*i] == '$')
	{
		(*i)++;
		if (value[*i - 1] == '?')
			return (ft_strdup("some stuff"));
		if (value[*i - 1] == '$')
			return (ft_strdup("some other stuff"));
	}
	if (!ft_isalpha(value[*i]) && value[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalpha(value[*i]) || value[*i] == '_')
		(*i)++;
	tmp = ft_substr(value, start, *i - start);
	if (!tmp)
		return (ft_strdup(""));
	result = getenv(tmp); //change to our envirement
	free(tmp);
	if (!result)
		return (ft_strdup(""));
	return (ft_strdup(result));
}

static void	expand_token(t_data *data, t_token *token, char *value)
{
	ssize_t	i;
	char	*tmp;
	char	*out;
	char	*buf;
	
	i = -1;
	out = ft_strdup("");
	if (!out)
		ft_exit(data, MAL_ERR, 1);
	while (value[++i])
	{
		buf = out;
		if (value[i] == '$')
		{
			i++;
			tmp = get_var_name(value, &i);
			if (!tmp)
				ft_exit(data, MAL_ERR, 1);
			out = ft_strjoin(out, tmp);
			free(buf);
			free(tmp);
			i--;
		}
		else
		{
			out = ft_charjoin(out, value[i]);
			if (!out)
				ft_exit(data, MAL_ERR, 1);
			free(buf);
		}
	}
	free(token->value);
	token->value = out;
}

void	expander(t_data *data)
{
	t_token	*ptr;

	ptr = data->token;
	return ;
	while (ptr)
	{
		if (ptr->type == TOKEN_WORD && ptr->quote != QUOTE_SINGLE)
			expand_token(data, ptr, ptr->value);
		if (!ptr->value)
			ft_exit(data, MAL_ERR, 1);
		ptr = ptr->next;
	}
}