/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:06:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 17:06:50 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char **env, char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (env[i])
	{
		if (!ft_strncmp(s, env[i], len) && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}
