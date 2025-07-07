/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_head.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:15:15 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/07 16:26:28 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HEAD_H
# define MINISHELL_HEAD_H

// printf, perror
# include <stdio.h>

// malloc, free, exit, getenv
# include <stdlib.h>

// write, access, read, close, fork, getcwd, chdir,
// execve, dup, dup2, pipe, isatty, ttyname, ttyslot,
# include <unistd.h>

// strerror
# include <string.h>

// opendir, readdir, closedir
# include <dirent.h>

// stat, lstat, fstat, unlink
# include <sys/stat.h>

// wait, waitpid, wait3, wait4
# include <sys/wait.h>

// signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>

// open
# include <fcntl.h>

// errno
# include <errno.h>

// ioctl
# include <sys/ioctl.h>

// libft
// # include "libft.h"

// tcsetattr, tcgetattr, tgetent
# include <termios.h>

# include <readline/readline.h>

# include <readline/history.h>

#endif