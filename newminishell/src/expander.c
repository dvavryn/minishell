/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:16:39 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/09 17:33:13 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_str(t_data *data, char **s)
{
	(void)data;
	(void)s;
		// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
	// TODOTODOTODOTODOTODOTODO
}

void	expand(t_data *data, t_cmd *cmd)
{
	ssize_t	i;

	if (!ft_strchr(cmd->cmd, '\''))
		expand_str(data, &cmd->cmd);
	if (cmd->redir_in == R_IN && !ft_strchr(cmd->file_in, '\''))
		expand_str(data, &cmd->file_in);
	if (cmd->redir_out)
		expand_str(data, &cmd->file_out);
	i = -1;
	while (cmd->args[++i])
	{
		if (!ft_strchr(cmd->args[i], '\''))
			expand_str(data, &cmd->args[i]);
	}
}

int	expander(t_data *data)
{
	t_cmd	*ptr;

	ptr = data->cmd;
	while (ptr)
	{
		expand(data, ptr);
		ptr = ptr->next;
	}
	return (0);
}
