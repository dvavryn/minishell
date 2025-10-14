/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:47:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/14 15:55:53 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_var()
{
	return (0);	
}

int	add_export_list()
{
	return (0);
}

int bi_export(t_data *data, t_cmd *cmd)
{
	size_t	i;
	char	*arg;
	// char	*ptr;
	
	i = 1;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		if (ms_getenv(data->env, arg))
			printf("%s\n", ms_getenv(data->env, arg));
		i++;
	}
	return (0);
}