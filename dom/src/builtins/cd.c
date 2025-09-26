/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:12:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 12:36:28 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_cd(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	printf("TODO!!\n");
	return (0);
	// char	*curpath;
	// int		ret;

	// (void)curpath;
	// if (!cmd->args[1])
	// {
	// 	if (!ms_getenv(data->env, "HOME"))
	// 		return (ft_putendl_fd("minishell: cd: HOME is unset",
	// 				STDERR_FILENO), 1);
	// 	else
	// 		ret = chdir(ms_getenv(data->env, "HOME"));
	// }
	// else
	// {
	// 	if (cmd->args[1][0] == '/')
	// 		ret = chdir(cmd->args[1]);
	// 	if (!ft_strncmp(cmd->args[1], ".", 1)
	// 		|| !ft_strncmp(cmd->args[1], "..", 2))
	// 	{
	// 	}
	// }
	// if (ret == -1)
	// 	perror("minishell: cd");
	// return (ret);
}
