/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:45:56 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/12 13:55:50 by dvavryn          ###   ########.fr       */
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
	int				heredoc_fd;
	t_token_type	type;
	t_token_quote	quote;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;		// first TOKEN_WORD
	char			**args;		// every other TOKEN_WORD before the next special character, | < > << >>
	int				pipe_in;	// every command besides the first one
	int				pipe_out;	// if there is a next command;
	char			*file_in;	// infile filename, if if R_HEREDOC limiter
	int				redir_in;	// infile flag if R_IN or R_HEREDOC
	char			*file_out;	// otufile filename 
	int				redir_out;	// outfile flag if R_OUT or R_APPEND
	int				fd_in;		// init at -1;
	int				fd_out;		// init at -1;
	struct s_cmd	*next;		// ptr to next command
}	t_cmd;

typedef struct s_data
{
	char	**env;
	char	*input;
	t_token	*token;
	t_cmd	*cmd;
	size_t	line;
	ssize_t	i;
}	t_data;

#endif