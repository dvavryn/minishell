/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:21:10 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 15:41:41 by dvavryn          ###   ########.fr       */
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
# include "../libft/libft.h"

typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR,
	TOKEN_TO_EXPAND,
	TOKEN_QUOTE,
	TOKEN_HEREDOC,
}	t_token_type;

typedef enum e_redir_type
{
	R_NONE,
	R_IN,
	R_HEREDOC,
	R_OUT,
	R_APPEND,
}	t_redir_type;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;		// first TOKEN_WORD
	char			**args;		// every other TOKEN_WORD before the next
								// special character, | < > << >>
	int				pipe_in;	// every command besides the first one
	int				pipe_out;	// if there is a next command;
	char			*file_in;	// infile filename, if if R_HEREDOC limiter
	int				redir_in;	// infile flag if R_IN or R_HEREDOC
	char			*file_out;	// otufile filename 
	int				redir_out;	// outfile flag if R_OUT or R_APPEND
	struct s_cmd	*next;		// ptr to next command
}	t_cmd;

typedef struct s_data
{
	char	**env;
	char	**export_list;
	char	*input;
	size_t	i;
	t_token	*tokens;
	t_cmd	*cmd;
	size_t	line;
	int		ret;
}	t_data;

void	free_all(t_data *data);
int		prompt(t_data *data);
void	startup(t_data *data, int argc, char **argv, char **envp);
void	ft_exit(t_data *data, char *error);
void	free_tokens(t_token *tokens);
void	tokenize(t_data *data);
void	ft_perror(char *s);
int		parser(t_data *data);
void	free_cmd(t_cmd *cmd);
int		expander(t_data *data);
void	executer(t_data *data);

int		isbuiltin(char *s);
void	bi_exit(t_data	*data, char **args);
int		bi_echo(t_cmd *cmd);
void	bi_env(t_data *data);
void	bi_pwd(char **env);
int		bi_export(t_data *data, t_cmd *cmd);
int		bi_unset(t_data *data, t_cmd *cmd);
int		bi_cd(t_data *data, t_cmd *cmd);
char	**add_split(char **arr1, char *str);
char	*ms_getenv(char **env, char *s);
void	get_all_args(t_data *data);
int		check_files(t_data *data);
int		check_binaries(t_data *data);
#endif