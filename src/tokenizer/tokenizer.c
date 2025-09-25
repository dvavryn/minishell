/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:32:46 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 17:15:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_data *data)
{
	while (data->input[data->i])
	{
		while (data->input[data->i] && ft_strchr(" \t", data->input[data->i]))
			data->i++;
		if (data->input[data->i] == '|')
			add_token_pipe(data);
		else if (data->input[data->i] == '<' || data->input[data->i] == '>')
			add_token_redir(data);
		else
			add_token_word(data);
	}
}
