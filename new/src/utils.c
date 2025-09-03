/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:35:20 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 18:43:13 by dvavryn          ###   ########.fr       */
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

void	ft_exit(t_data *data, int ret, int err)
{
	if (err && ret == 1)
		;
	else if (err && ret == MAL_ERR)
		write(STDERR_FILENO, "minishell: crash: malloc failed\n", 32);
	else if (err && ret == 3)
		;
	if (data->input)
		free(data->input);
	if (data->token)
		free_token(data->token);
	if (data->envp)
		free_split(data->envp);
	exit(ret);
}

char	**copy_split(char **to_copy)
{
	char	**out;
	ssize_t	i;

	i = -1;
	while (to_copy[++i])
		;
	out = ft_calloc(i + 2, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
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