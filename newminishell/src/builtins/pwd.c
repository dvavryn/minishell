/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:31 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/15 17:06:14 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(char **env)
{
	if (!env || !*env)
		return ;
	ft_putendl_fd(ms_getenv(env, "PWD"), STDOUT_FILENO);
}

// i = 0;
// while (env[i])
// {
// 	if (!ft_strncmp(env[i], "PWD=", 4))
// 	{
// 		ft_putendl_fd(4], STDOUT_FILENO);
// 		return ;
// 	}
// 	i++;
// }