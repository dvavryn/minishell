/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:39:10 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/24 11:12:29 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void	heredoctocmd(t_token *tmp, t_cmd *curr)
{
	
}

static void	pipetocmd(t_cmd *curr)
{
	curr->pipe_out = 1;
	curr = curr->next;
	curr->pipe_in = 1;
	curr->fd_in = -1;
	curr->fd_out = -1;
}

void	assign_cmd(t_data *data)
{
	t_token	*tmp;
	t_cmd	*curr;

	data->i = 0;
	tmp = data->token;
	curr = data->cmd;
	curr->fd_in = -1;
	curr->fd_out = -1;
	while (tmp)
	{
		// if (tmp->type == TOKEN_HEREDOC)
			// heredoctocmd(tmp, curr);
		// if (tmp->type == TOKEN_APPEND_OUT)
			// appendtocmd(tmp, curr);
		if (tmp->type == TOKEN_WORD)
		{
			if (!curr->cmd)
				curr->cmd = tmp->value;
			else
				curr->args[data->i++] = tmp->value;
		}
		if (tmp->next && tmp->next->type == TOKEN_PIPE)
			pipetocmd(curr);
		tmp = tmp->next;
	}
}
