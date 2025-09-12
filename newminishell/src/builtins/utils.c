/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:12:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/11 12:13:44 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char *s)
{
	if (!ft_strcmp("exit", s))
		return (1);
	if (!ft_strcmp("echo", s))
		return (1);
	if (!ft_strcmp("cd", s))
		return (1);
	if (!ft_strcmp("pwd", s))
		return (1);
	if (!ft_strcmp("export", s))
		return (1);
	if (!ft_strcmp("unset", s))
		return (1);
	if (!ft_strcmp("env", s))
		return (1);
	return (0);
}
