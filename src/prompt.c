/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:46:27 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 19:48:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_data *data)
{
	data->last_ret = data->ret;
	data->input = NULL;
	if (data->ret)
		printf ("[%d] ", data->ret);
	data->ret = 0;
	data->input = readline("minishell > ");
	if (!data->input)
		bi_exit(data, 0);
	if (!*data->input)
	{
		free(data->input);
		return (0);
	}
	if (*data->input && *data->input != ' ' && *data->input != '\t')
		add_history(data->input);
	data->i = 0;
	data->line++;
	return (1);
}
