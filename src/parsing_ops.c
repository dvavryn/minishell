/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:47:58 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/25 13:55:50 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	if (TOKEN_WORD)
		free(TOKEN_WORD);
	if (TOKEN_PIPE)
		free(TOKEN_PIPE);
	// if (TOKEN_REDIR_IN)
	// 	free(TOKEN_REDIR_IN);
	// if (TOKEN_REDIR_OUT)
	// 	free(TOKEN_REDIR_OUT);
}

char	*read_quotes(char *input, ssize_t *i)
{
	int		start;
	char	quote;
	char	*word;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		//error endet nicht mit quote
		return (NULL);
	}
	word = ft_strndup(&input[start],  *i - start);
	if (input[*i] == quote)
		(*i)++;
	return (word);
}
