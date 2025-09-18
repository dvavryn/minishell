/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:10:46 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 13:12:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->token)
		free_tokens(data->token);
	// if (data->cmd)
	// 	free_cmd(data->cmd);
	// if (data->env)
	// 	free_split(data->env);
	if (data->export_list)
		free_split(data->export_list);
	data->input = NULL;
	data->token = NULL;
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