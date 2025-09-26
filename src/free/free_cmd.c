/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 17:38:02 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*ptr;

	while (cmd)
	{
		ptr = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->file_in && cmd->redir_in == R_HEREDOC)
			unlink(cmd->file_in);
		if (cmd->file_in)
			free(cmd->file_in);
		if (cmd->file_out)
			free(cmd->file_out);
		if (cmd->args)
			free_split(cmd->args);
		free(cmd);
		cmd = ptr;
	}
}
