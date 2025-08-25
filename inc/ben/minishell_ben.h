/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ben.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:26:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/25 15:10:55 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BEN_H
# define MINISHELL_BEN_H

# include "libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
}   t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token	*lex_input(char *str);
void	free_tokens(t_token *token);
void	print_tokens(t_token *token);
char	*read_quotes(char *input, ssize_t *i);
// char	*expand_token_value(const char *value);

#endif