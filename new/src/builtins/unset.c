/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:06:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 14:30:31 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cleanup(t_data *data, ssize_t del)
{
	ssize_t	i;
	char	**buf;
	
	buf = data->envp;
	i = -1;
	while (buf[++i])
		;
	data->envp = ft_calloc(i, sizeof(char *));
	if (!data->envp)
		ft_exit(data, MAL_ERR, MAL_ERR);
	i = -1;
	while (data->envp[i])
	{
		if (i < del)
			data->envp[i] = buf[i];
		else if (i > del)
			data->envp[i] = buf[i + 1];
	}
}

// no stdin no stdout
int	builtin_unset(t_data *data, char **cmd)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len;

	// no env
	if (!data->envp || !data->envp[0])
		return (0);
	i = 0;
	while (cmd[++i])
	{
		j = -1;
		len = ft_strlen(cmd[i]);
		if (!ft_strncmp(cmd[i], data->envp[i], len)
			&& ft_strcmp(cmd[i], "_") && cmd[i][len + 1] == '=')
			cleanup(data, i);
	}
	return (0);
}