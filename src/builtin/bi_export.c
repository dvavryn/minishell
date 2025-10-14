/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:47:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/14 18:52:00 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_exportlist(char **export_list, ssize_t i, ssize_t j, int flag)
{
	if (!export_list)
		return (1);
	while (export_list[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (ft_strchr(export_list[i], '='))
		{
			j = -1;
			while (export_list[i][++j])
			{
				ft_putchar_fd(export_list[i][j], STDOUT_FILENO);
				if (export_list[i][j] == '=' && !flag)
				{
					flag = 1;
					ft_putchar_fd('"', STDOUT_FILENO);
				}
			}
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(export_list[i], STDOUT_FILENO);
	}
	return (0);
}

char	*replace_env_sub(char *arg, size_t j, size_t k)
{
	char	*a;
	char	*b;
	char	*out;

	a = ft_substr(arg, 0, j);
	if (!a)
		return (NULL);
	b = ft_substr(arg, j + k, ft_strlen(&arg[j + k] - k));
	if (!b)
		return (free(a), NULL);
	out = ft_strjoin(a, b);
	return (free(a), free(b), out);
}

void	replace_env(t_data *data, char *arg, size_t i)
{
	ssize_t	j;
	size_t	k;
	char	*tmp;

	j = -1;
	while (data->env[++j])
	{
		if (!ft_strncmp(data->env[j], arg, i))
			break ;
	}
	k = (arg[j + 1] == '"');
	tmp = replace_env_sub(arg, j, k);
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

int	bi_export(t_data *data, t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	int		flag;

	if (!cmd->args[1])
		return (print_exportlist(data->export_list, -1, -1, 0), 0);
	i = 0;
	while (cmd->args[++i])
	{
		j = 0;
		while (cmd->args[i][j] && cmd->args[i][j] != '=')
			j++;
		tmp = ft_substr(cmd->args[i], 0, j);
		if (!tmp)
			ft_exit(data, "malloc");
		flag = (!ms_getenv(data->env, tmp)) * 1;
		free(tmp);
		if (!flag)
			replace_env(data, cmd->args[i], j);
		else
			add_env(data, cmd->args[i]);
	}
	return (0);
}
