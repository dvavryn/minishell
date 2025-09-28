/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:12:21 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/27 20:03:36 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd_word(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if (!(*cmd)->cmd)
	{
		(*cmd)->cmd = ft_strdup(ptr->value);
		if (!(*cmd)->cmd)
			ft_exit(data, "memory allocation");
	}
	else
		split_join(data, *cmd, ptr->value);
}

t_redir *new_redir(t_data *data, t_token *token)
{
	t_redir	*out;

	out = ft_calloc(1, sizeof(t_redir));
	if (!out)
		return (NULL);
	if (!ft_strcmp(token->value, "<<"))
		get_heredoc(data, &token->next->value);
	out->filename = ft_strdup(token->next->value);
	if (!out->filename)
		return (free(out), NULL);
	if (!ft_strcmp(token->value, "<") || !ft_strcmp(token->value, "<<"))
		out->type = R_IN;
	else if (!ft_strcmp(token->value, ">"))
		out->type = R_OUT;
	else if (!ft_strcmp(token->value, ">>"))
		out->type = R_APPEND;
	return (out);
}

static void	add_cmd_redir(t_data *data, t_token *token, t_cmd **cmd)
{
	t_redir	*ptr;

	if (!(*cmd)->redirs)
	{
		(*cmd)->redirs = new_redir(data, token);
		if (!(*cmd)->redirs)
			ft_exit(data, "malloc");
	}
	else
	{
		ptr = (*cmd)->redirs;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_redir(data, token);
		if (!ptr->next)
			ft_exit(data, "malloc");
	}
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
			add_cmd_redir(data, ptr, &cmd);
			ptr = ptr->next;
		}
		else
			add_cmd_word(data, ptr, &cmd);
		ptr = ptr->next;
	}
}
