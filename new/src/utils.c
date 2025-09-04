/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:20 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/04 14:15:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	ssize_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static void	ft_error(int err)
{
	write(2, "minishell: crash: ", 17);
	if (err == MAL_ERR)
		write(2, "malloc failed", 13);
	write(2, "\n", 1);
}

void	ft_exit(t_data *data, int ret, int err)
{
	if (err != 0)
		ft_error(err);
	if (data->input)
		free(data->input);
	if (data->token)
		free_token(data->token);
	if (data->envp)
		free_split(data->envp);
	if (err)
		ret = err;
	exit(ret);
}

char	**copy_split(char **to_copy)
{
	char	**out;
	ssize_t	i;

	i = -1;
	while (to_copy[++i])
		;
	out = ft_calloc(i + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	if (!to_copy[0])
	{
		out[0] = NULL;
		return (out);
	}
	while (to_copy[++i])
	{
		out[i] = ft_strdup(to_copy[i]);
		if (!out[i])
		{
			free_array(out, i);
			return (NULL);
		}
	}
	return (out);
}
