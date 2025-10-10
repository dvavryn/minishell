/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/01 13:50:59 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*ptr;

	while (redir)
	{
		ptr = redir->next;
		if (redir->type == R_HEREDOC && redir->filename)
			unlink(redir->filename);
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = NULL;
		redir = ptr;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*ptr;

	while (cmd)
	{
		ptr = cmd->next;
		if (cmd->redirs)
			free_redir(cmd->redirs);
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			free_split(cmd->args);
		free(cmd);
		cmd = ptr;
	}
}
