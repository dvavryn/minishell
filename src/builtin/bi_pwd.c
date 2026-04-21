/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:14:58 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 19:55:31 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(t_data *data)
{
	char	*pwd;

	pwd = ms_getenv(data->env, "PWD");
	if (!pwd)
	{
		data->ret = 1;
		return ;
	}
	if (-1 == write (STDOUT_FILENO, pwd, ft_strlen(pwd)))
		data->ret = 1;
	if (-1 == write(STDOUT_FILENO, "\n", 1))
		data->ret = 1;
}
