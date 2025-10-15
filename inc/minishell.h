/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:02:11 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 17:05:13 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// header
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

// typedefs
typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_expand		t_expand;
typedef struct s_redir		t_redir;
typedef struct s_exec		t_exec;
typedef enum e_token_type	t_token_type;
typedef enum e_redir_type	t_redir_type;

// enum
enum e_token_type
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR,
	TOKEN_TO_EXPAND,
	TOKEN_QUOTE,
	TOKEN_HEREDOC,
};

enum e_redir_type
{
	R_NONE,
	R_IN,
	R_HEREDOC,
	R_OUT,
	R_APPEND,
};

// structs
struct s_data
{
	char	**env;
	char	**export_list;
	char	*input;
	size_t	i;
	t_token	*tokens;
	t_cmd	*cmd;
	size_t	line;
	int		ret;
	int		hd_quit;
	// ret error return...
		// syntax error = 2
};

struct s_token
{
	char	*value;
	int		type;
	int		expanded;
	t_token	*next;
};

struct s_redir
{
	char	*filename;
	int		type;	
	t_redir	*next;
};

struct s_cmd
{
	char	*cmd;
	char	**args;
	int		pipe_in;
	int		pipe_out;
	t_redir	*redirs;
	t_cmd	*next;
};

struct s_expand
{
	char	*out;
	char	*buf1;
	char	*buf2;
	char	*ptr;
	size_t	i;
	int		flag;
};

struct s_exec
{
	int		pid;
	int		pipe[2][2];
	int		redir_in;
	int		redir_out;
	int		status;
	int		ret;
	size_t	curr;
	size_t	cmd_count;
};

// prototypes
// general
void	startup(t_data *data, int argc, char **argv, char **envp);
char	**copy_env(char **envp);
int		prompt(t_data *data);
void	ft_exit(t_data *data, char *error);

// builtins
void	bi_exit(t_data	*data, char **args);
void	bi_env(t_data *data);
int		bi_echo(t_data *data, char **args);
void	bi_pwd(t_data *data);
int		bi_unset(t_data *data, t_cmd *cmd, char **export_list);
int		bi_export(t_data *data, t_cmd *cmd);
int		bi_cd(t_data *data, t_cmd *cmd);

// tokenize
void	tokenize(t_data *data);
void	add_token_pipe(t_data *data);
void	add_token_redir(t_data *data);
void	add_token_word(t_data *data);

// parser
int		parser(t_data *data);
int		isclosed(char *s);
void	get_cmd(t_data *data);
void	add_cmd(t_data *data);

// parser/heredoc
int		get_heredoc(t_data *data, char **lim);
char	*get_heredoc_name(void);
char	*get_heredoc_input(t_data *data, char *lim, char *out);
char	*clean_hd(char *in);
void	cmd_split_join(t_data *data, t_cmd *cmd, char *value);
char	*expand_heredoc(t_data *data, char *input);
void	cleanup_args(t_data *data);

// expander
void	expander(t_data *data);
void	expanded_tokens(t_data *data);

// executer
int		executer(t_data *data);
char	*get_path(t_data *data, t_cmd *cmd);
int		isbuiltin(char *s);
void	init_exec(t_data *data, t_exec *exec);
void	pipeline(t_data *data, t_cmd *cmd, t_exec *exec);
int		open_files(t_redir *red, t_exec *ex);
int		dup_child(t_exec *exec, size_t c);
void	close_fds(t_exec *exec);

// utils
char	*ft_strjoin_endl(char *s1, char *s2);
char	*ms_getenv(char **env, char *s);
char	**split_copy(char **arr);
void	ms_perror(const char *str, ...);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
t_token	*ms_lstlast(t_token *lst);

// signals
void	sig_interactive(void);
void	sig_execute_parent(void);
void	sig_execute_child(void);

// free
void	free_all(t_data *data);
void	free_split(char **split);
void	free_split_rev(char **out, size_t i);
void	free_tokens(t_token *tokens);
void	free_cmd(t_cmd *cmd);

// debug delete after
void	print_tokens(t_token *tokens);
void	print_cmds(t_cmd *ptr);

#endif