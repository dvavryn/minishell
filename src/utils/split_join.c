/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:23:59 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 16:25:31 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_join_sub(t_data *data, t_cmd **cmd, char *value)
{
	(*cmd)->args = ft_split(value, '\0');
	if (!(*cmd)->args)
		ft_exit(data, "malloc");
}

void	split_join(t_data *data, t_cmd *cmd, char *value)
{
	char	**out;
	char	*buf;
	size_t	i;

	if (!cmd->args)
		split_join_sub(data, &cmd, value);
	else
	{
		buf = ft_strdup(value);
		if (!buf)
			ft_exit(data, "malloc");
		out = split_copy(cmd->args);
		if (!out)
		{
			free(buf);
			ft_exit(data, "malloc");
		}
		i = 0;
		while (out[i])
			i++;
		out[i] = buf;
		cmd->args = out;
	}
}
