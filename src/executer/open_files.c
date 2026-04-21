/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:21:35 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/01 13:20:27 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_files_sub(int mode, int *fd, char *file)
{
	if (*fd != -1)
		close(*fd);
	if (mode == R_IN)
		*fd = open(file, O_RDONLY);
	else if (mode == R_OUT)
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	else if (mode == R_APPEND)
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (*fd == -1)
		return (1);
	return (0);
}

int	open_files(t_redir *red, t_exec *ex)
{
	int	flag;

	flag = 0;
	while (red)
	{
		if (red->type == R_IN)
			flag = open_files_sub(red->type, &ex->redir_in, red->filename);
		else
			flag = open_files_sub(red->type, &ex->redir_out, red->filename);
		if (flag)
		{
			perror(red->filename);
			if (ex->redir_in != -1)
				close(ex->redir_in);
			if (ex->redir_out != -1)
				close(ex->redir_out);
			return (0);
		}
		red = red->next;
	}
	return (1);
}
