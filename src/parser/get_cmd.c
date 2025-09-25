/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:12:21 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 16:34:33 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd_word(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if (!(*cmd)->cmd)
	{
		(*cmd)->cmd = ft_strdup(ptr->value);
		if (!(*cmd)->cmd)
			ft_exit(data, "malloc");
	}
	else
		split_join(data, *cmd, ptr->value);
}

static void	add_cmd_redir_in(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if (ptr->value[0] != ptr->value[1])
		(*cmd)->redir_in = R_IN;
	else
		(*cmd)->redir_in = R_HEREDOC;
	if ((*cmd)->file_in)
		free((*cmd)->file_in);
	(*cmd)->file_in = ft_strdup(ptr->next->value);
	if (!(*cmd)->file_in)
		ft_exit(data, "malloc");
	if ((*cmd)->redir_in == R_HEREDOC)
	{
		if (!get_heredoc(data, &(*cmd)->file_in))
			ft_exit(data, "malloc");
	}
}

static void	add_cmd_redir_out(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if (ptr->value[0] != ptr->value[1])
		(*cmd)->redir_out = R_OUT;
	else
		(*cmd)->redir_out = R_APPEND;
	if ((*cmd)->file_out)
		free((*cmd)->file_out);
	(*cmd)->file_out = ft_strdup(ptr->next->value);
	if (!(*cmd)->file_out)
		ft_exit(data, "malloc");
}

static void	add_cmd_pipe(t_data *data, t_cmd **cmd)
{
	add_cmd(data);
	(*cmd)->pipe_out = 1;
	*cmd = (*cmd)->next;
	(*cmd)->pipe_in = 1;
}

void	get_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_token	*ptr;

	add_cmd(data);
	cmd = data->cmd;
	ptr = data->tokens;
	while (ptr)
	{
		if (ptr->type == TOKEN_PIPE)
			add_cmd_pipe(data, &cmd);
		else if (ptr->type == TOKEN_REDIR || ptr->type == TOKEN_HEREDOC)
		{
			if (!ft_strcmp(ptr->value, "<") || !ft_strcmp(ptr->value, "<<"))
				add_cmd_redir_in(data, ptr, &cmd);
			else
				add_cmd_redir_out(data, ptr, &cmd);
			ptr = ptr->next;
		}
		else
			add_cmd_word(data, ptr, &cmd);
		ptr = ptr->next;
	}
}
