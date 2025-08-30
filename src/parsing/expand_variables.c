/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:49:04 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/30 14:30:26 by bschwarz         ###   ########.fr       */
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

	if (value[*i] == '?')
	{
		(*i)++;	
		return (ft_strdup("some stuff"));
	}
	if (value[*i] == '$')
	{
		(*i)++;	
		return (ft_strdup("some other stuff"));
	}
	if (!ft_isalpha(value[*i]) && value[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalpha(value[*i]) || value[*i] == '_')
		(*i)++;
	tmp = ft_substr(value, start, *i - start);
	if (!tmp)
		return (ft_strdup("")); //return NULL with check
	result = getenv(tmp); //change to our envirement
	free(tmp);
	if (!result)
		return (ft_strdup(""));
	return (ft_strdup(result));
}

static void	expand_token_value(t_token *token, char *value)
{
	ssize_t	i;
	char	*tmp;
	char	*result;
	
	i = -1;
	result = ft_strdup("");
	while (value[++(i)])
	{
		if (value[i] == '$')
		{
			i++;
			tmp = get_var_name(value, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			i--;
		}
		else
			result = ft_charjoin(result, value[i]);
	}
	free(token->value);
	token->value = result;
}

void	expand_token(t_token *token)
{
	t_token	*cur;
		
	if (!token)
		return ;
	cur = token;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && cur->quote != 1)
			expand_token_value(cur, cur->value);
		cur = cur->next;
	}
}
