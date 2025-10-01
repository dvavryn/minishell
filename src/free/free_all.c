/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:14:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/01 14:35:02 by dvavryn          ###   ########.fr       */
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
	data->input = NULL;
	data->tokens = NULL;
	data->cmd = NULL;
	data->env = NULL;
}
	