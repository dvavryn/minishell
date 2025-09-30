/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:14:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/30 13:39:45 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmd)
		free_cmd(data->cmd);
	if (data->env)
		free_split(data->env);
	// if (data->export_list)
		// free_split(data->export_list);
	data->input = NULL;
	data->tokens = NULL;
	data->cmd = NULL;
	data->env = NULL;
	// data->export_list = NULL;
	(void)data; // to remove
}
