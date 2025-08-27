/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:49:04 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 15:03:05 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	c;
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
		{
			c = value[i];
			result = ft_strjoin(result, &c);
		}
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
