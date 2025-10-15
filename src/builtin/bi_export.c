/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:47:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 21:26:57 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env_sub(char *arg, size_t j, size_t k)
{
	char	*a;
	char	*b;
	char	*out;

	a = ft_substr(arg, 0, j);
	if (!a)
		return (NULL);
	b = ft_substr(arg, j + k, ft_strlen(&arg[j + k]) - k);
	if (!b)
		return (free(a), NULL);
	out = ft_strjoin(a, b);
	return (free(a), free(b), out);
}

void	replace_env(t_data *data, char *arg, size_t equal)
{
	ssize_t	j;
	char	*tmp;

	if (!ft_strchr(arg, '='))
		return ;
	j = -1;
	while (data->env[++j])
	{
		if (!ft_strncmp(data->env[j], arg, equal)
			&& (data->env[j][equal] == '=' || ft_strlen(data->env[j]) == equal))
			break ;
	}
	tmp = ft_strdup(arg);
	if (!tmp)
		ft_exit(data, "malloc");
	free(data->env[j]);
	data->env[j] = tmp;
}

void	add_env(t_data *data, char *arg)
{
	ssize_t	i;
	char	**out;

	i = -1;
	while (data->env[++i])
		;
	out = ft_calloc(i + 2, sizeof(char *));
	if (!out)
		ft_exit(data, "malloc");
	i = -1;
	while (data->env[++i])
		out[i] = data->env[i];
	out[i] = ft_strdup(arg);
	if (!out[i])
	{
		free(out);
		ft_exit(data, "malloc");
	}
	free(data->env);
	data->env = out;
}

static int	bi_export_loop(t_data *data, int flag, char *arg, size_t j)
{
	char	*tmp;

	if (isvalidvar(arg))
	{
		while (arg[j] && arg[j] != '=')
			j++;
		tmp = ft_substr(arg, 0, j);
		if (!tmp)
			ft_exit(data, "malloc");
		flag = (!isexported(data->env, tmp)) * 1;
		free(tmp);
		if (!flag)
			replace_env(data, arg, j);
		else
			add_env(data, arg);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		data->ret = 1;
	}
	return (0);
}

int	bi_export(t_data *data, t_cmd *cmd)
{
	size_t	i;

	if (!cmd->args[1])
		return (print_exportlist(data->env, -1, -1, 0), 0);
	i = 0;
	while (cmd->args[++i])
		bi_export_loop(data, 0, cmd->args[i], 0);
	return (0);
}
