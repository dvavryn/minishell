/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:34:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 15:49:28 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND_OUT,
}	t_token_type;

typedef enum e_token_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_HD,
}	t_token_quote;

typedef enum e_errors
{
	NO_ERR,
	DUNNO,
	MAL_ERR,
}	t_errors;

typedef struct s_token
{
	char			*value;
	int				heredoc_fd;
	t_token_type	type;
	t_token_quote	quote;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	*input;
	size_t	i;
	t_token	*token;
	char	**envp;
	int		last_return_value;
}	t_data;

// utils.c
void	ft_exit(t_data *data, int ret, int err);
void	free_split(char **split);
char	**copy_split(char **to_copy);

// prompt.c
int		prompt(t_data *data);

// startup.c
void	startup(t_data *data, int argc, char **argv, char **envp);

// tokenize/
int		tokenize(t_data *data);
void	free_token(t_token	*token);

// builtins/
void	builtin_exit(t_data *data);

// debugging/
void	print_token(t_token *token);

// expander/
void	expander(t_data *data);

// parser/
int	parser(t_data *data);

#endif