/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ben.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:26:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/27 13:11:44 by bschwarz         ###   ########.fr       */
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
}	t_token_type;

typedef enum e_token_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_token_quote;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_quote	quote;
	struct s_token	*next;
}	t_token;

t_token	*lex_input(char *str);
void	free_tokens(t_token *token);
void	print_tokens(t_token *token);
// void	expand_token(t_token *token);
void	add_token(t_token **token, t_token *new);
t_token	*new_token(char *value, int type, int quote);
t_token	*add_word_token(t_token *token, char *input, ssize_t *i);

#endif