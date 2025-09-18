/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:47:25 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 13:09:31 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **arr)
{
	ssize_t	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_all(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmd)
		free_cmd(data->cmd);
	// if (data->env)
	// 	free_split(data->env);
	if (data->export_list)
		free_split(data->export_list);
	data->input = NULL;
	data->tokens = NULL;
	data->cmd = NULL;
	// data->env = NULL;
	data->export_list = NULL;
}

void	ft_exit(t_data *data, char *error)
{
	if (!ft_strcmp("malloc", error))
		write(2, "minishell: error: memory allocation failed\n", 43);
	if (!ft_strcmp("fork", error))
		write(2, "minishell: error: fork failed\n", 31);
	if (!ft_strcmp("open", error))
		write(2, "minishell: error: open failed\n", 30);
	if (!ft_strcmp("pipe", error))
		write(2, "minishell: error: pipe failed\n", 31);
	free_all(data);
	exit(1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*ptr;

	while (tokens)
	{
		ptr = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = ptr;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*ptr;

	while (cmd)
	{
		ptr = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->file_in && !ft_strncmp(cmd->file_in, ".heredoc", 8))
			unlink(cmd->file_in);
		if (cmd->file_in)
			free(cmd->file_in);
		if (cmd->file_out)
			free(cmd->file_out);
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		if (cmd->fd_out > 0)
			close(cmd->fd_out);
		free(cmd);
		cmd = ptr;
	}
}
