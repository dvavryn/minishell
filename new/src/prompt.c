/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:37:01 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:42:47 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_data *data)
{
	data->input = readline("minishell > ");
	if (!data->input)
	{
		printf("exit\n");
		ft_exit(data, NO_ERR, 0);
	}
	else if (*data->input == 0)
	{
		free(data->input);
		return (0);
	}
	// standard bash behaviour -- PC's on campus dont do this?!?!
	if (!ft_isspace(*data->input))
		add_history(data->input);
	data->i = 0;
	return (1);
}
