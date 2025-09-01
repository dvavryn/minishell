/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:45:56 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/01 14:35:53 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND_OUT
}	t_token_type;

typedef enum e_token_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_HD
}	t_token_quote;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_quote	quote;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	**env;
	t_token	*token;
	char	*input;
	ssize_t	i;
}	t_data;

#endif