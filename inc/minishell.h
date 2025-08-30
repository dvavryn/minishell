/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:24:06 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/30 12:21:14 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ============================== CORE HEADER =================================

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

// ============================ UTILITY HEADER ================================

# include "macros.h"
# include "structs.h"

// ===========================  PERSONAL HEADER ===============================

# include "dom/minishell_dom.h"
# include "ben/minishell_ben.h"

// ============================================================================

void	ft_executor(t_token *tokens, char **envp);
void	free_split(char **split);
int		ft_strcmp(const char *s1, const char *s2);

#endif