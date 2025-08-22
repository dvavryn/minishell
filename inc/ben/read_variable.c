/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:31:25 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/22 15:16:45 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_var_name(const char *str, int *i)
{
	int	start;
	int	len;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_strndup(str[start], len));
}

char	*expand_token_value(const char *value)
{
	int		i;
	char	*result;
	char	*var;
	
	i = 0;
	result = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			var = read_var_name(value, &i);
			if (ft_strcmp(var, "?") == 0)
				//sonderfall
			else if (ft_strlen(var) > 0)
				//variable verarbeiten
			else
			{
				free(var);
				var = ft_strdup("$");
			}
			result = ft_strjoin(result, var);
			free(var);
		}
		else
			result = ft_strjoin(result, value[i]);
	}
	return (result);
}
