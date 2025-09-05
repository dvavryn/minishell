/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:24:08 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 14:29:45 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_pwd(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (data->envp[++i] && !ft_strncmp("PWD=", data->envp[i], 4))
		;
	if (data->envp[i])
		printf("%s\n", &data->envp[i][4]);
}
