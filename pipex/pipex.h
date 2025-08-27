/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:45 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/27 12:09:36 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../inc/minishell.h"
# include "../libs/libft/libft.h"

typedef struct s_pipex
{
}	t_pipex;

typedef struct s_cmd
{
	int				in_mode;	// 0 - nothing 	// 1 - read 	// 2 - heredoc
	char			*infile;	// NULL			// path			// LIMITER
	char			**cmd;		// char ** -- NULL Terminated
	int				out_mode;	// 0 - STDOUT	// 1 - write	// 2 - append
	char			*outfile;	// NULL			// path
}	t_cmd;

typedef enum e_path_type
{
	SEARCH,
	ABSOLUTE,
	RELATIVE,
}	t_path_type;

char	**ft_split_join(char *to_split, char sep, char *to_join);
char	**get_path(char **envp, char *bin);
char	**get_cmd(int argc, char **argv);
char	*get_relative_path(char	*bin);
int		test_permissions(char *exe);
char	*shorten_path(char	*str);
void	free_split(char **split);
int		get_path_type(char *bin);
char	*get_access(char **path);

#endif