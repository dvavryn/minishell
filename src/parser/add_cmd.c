/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:22:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 12:36:48 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*out;

	out = ft_calloc(1, sizeof(t_cmd));
	if (!out)
		return (NULL);
	return (out);
}

void	add_cmd(t_data *data)
{
	t_cmd	*ptr;

	if (!data->cmd)
	{
		data->cmd = new_cmd();
		if (!data->cmd)
			ft_exit(data, "memory allocation");
	}
	else
	{
		ptr = data->cmd;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_cmd();
		if (!ptr->next)
			ft_exit(data, "memory allocation");
		ptr->next->next = NULL;
	}
}
