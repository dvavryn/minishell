/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:31 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 12:18:29 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(char **env)
{
	if (!env || !*env)
		return ;
	ft_putendl_fd(ms_getenv(env, "PWD"), STDOUT_FILENO);
}
