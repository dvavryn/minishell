/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:49:04 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 12:30:41 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static char	*get_var_name(const char *value, int *i)
// {
	
// }

// static void	expand_token_value(t_token *token)
// {
// 	ssize_t	*i;
// 	char	*tmp;
// 	char	*result;
	
// 	*i = -1;
// 	result = ft_strdup("");
// 	while (token->value[++(*i)])
// 	{
// 		if (token->value[*i] == '$')
// 		{
// 			*i++;
// 			tmp = get_var_name(token->value, &i);
// 			result = ft_strjoin(result, tmp);
// 			free(tmp);	
// 		}
// 		else
// 			result = ft_strjoin(result, token->value[*i]);
// 	}
// 	free(token->value);
// 	token->value = result;
// 	free(result);
// }

// void	expand_token(t_token *token)
// {
// 	t_token	*cur;
		
// 	if (!token)
// 		return ;
// 	cur = token;
// 	while (cur)
// 	{
// 		if (cur->type == TOKEN_WORD && token->quote != 1)
// 			expand_token_value(cur);
// 		cur = cur->next;
// 	}
// }
