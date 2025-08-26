/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:24:06 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 15:47:19 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===========================  PERSONAL HEADER ===============================

# include "dom/minishell_dom.h"
# include "ben/minishell_ben.h"
# include "macros.h"

// ============================================================================

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

// ============================================================================

#endif