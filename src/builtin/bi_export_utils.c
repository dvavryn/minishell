/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:54:47 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 21:00:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isexported(char **env, char *arg)
{
	ssize_t	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], arg, ft_strlen(arg)))
			return (1);
	return (0);
}

int	isvalidvar(char *var)
{
	ssize_t	i;

	i = -1;
	if (!ft_isalpha(var[0]))
		return (0);
	while (var[++i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]))
			return (0);
	}
	return (1);
}

int	print_exportlist(char **export_list, ssize_t i, ssize_t j, int flag)
{
	if (!export_list)
		return (1);
	while (export_list[++i])
	{
		if (ft_strchr(export_list[i], '='))
		{
			j = -1;
			while (export_list[i][++j])
			{
				ft_putchar_fd(export_list[i][j], STDOUT_FILENO);
				if (!flag && export_list[i][j] == '=')
				{
					flag = 1;
					ft_putchar_fd('"', STDOUT_FILENO);
				}
			}
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(export_list[i], STDOUT_FILENO);
		flag = 0;
		if (export_list[i + 1] && export_list[i + 1][0] == '_')
			i++;
	}
	return (0);
}
