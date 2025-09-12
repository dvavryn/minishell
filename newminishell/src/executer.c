/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:57:18 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/12 12:34:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_sub(t_data *data, char *s)
{
	char	**arr;
	char	*real;
	char	*buf;
	size_t	i;
	(void)data;

	real = ft_strjoin("/", s);
	if (!real)
		return (NULL);
	if (!ms_getenv(data->env, "PATH"))
		return (ft_strdup(s));
	arr = ft_split(ms_getenv(data->env, "PATH"), ':');
	if (!arr)
		return (free(real), NULL);
	i = -1;
	while (arr[++i])
	{
		buf = ft_strjoin(arr[i], real);
		if (!buf)
			return (free_split(arr), free(real), NULL);
		free(arr[i]);
		arr[i] = buf;
	}
	free(real);
	i = -1;
	while (arr[++i])
	{
		if (!access(arr[i], F_OK))
		{
			real = ft_strdup(arr[i]);
			break ;
		}
	}
	if (!arr[i])
		real = ft_strdup(s);
	free_split(arr);
	if (!real)
		return (NULL);
	return (real);
}

void	get_path(t_data *data, t_cmd *cmd)
{
	char *ptr;
	char *path;

	if (!cmd->cmd)
		return ;
	ptr = cmd->cmd;
	if (ft_strchr(ptr, '/'))
		path = ft_strdup(ptr);
	else
		path = get_path_sub(data, ptr);
	if (!path)
		ft_exit(data, "malloc");
	cmd->cmd = path;
	free(ptr);
}

int	check_binaries(t_data *data)
{
	t_cmd	*ptr;

	ptr = data->cmd;
	while (ptr)
	{
		if (ptr->cmd && !isbuiltin(ptr->cmd))
		{
			get_path(data, ptr);
			if (access(ptr->cmd, F_OK | X_OK))
			{
				perror(ptr->cmd);
				data->ret = 127;
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

int	check_files(t_data *data)
{
	t_cmd	*ptr;
	int		fd;

	ptr = data->cmd;
	while(ptr)
	{
		if (ptr->redir_in)
			if (access(ptr->file_in, F_OK | R_OK))
				return (perror(ptr->file_in), 0);
		if (ptr->redir_out)
		{
			if (access(ptr->file_out, F_OK))
			{
				fd = open(ptr->file_out, O_CREAT, 0666);
				if (fd == -1)
					return (perror(ptr->file_out), 0);
				close(fd);
			}
			if (access(ptr->file_out, F_OK | W_OK))
				return (perror(ptr->file_out), 0);
			fd = open(ptr->file_out, O_APPEND | O_WRONLY);
			if (fd == -1)
				return (perror(ptr->file_out), 0);
			close(fd);
		}
		ptr = ptr->next;
	}
	return (1);
}

void	get_all_args_sub(t_cmd *cmd)
{
	char	**out;
	ssize_t	i;

	i = -1;
	while (cmd->args[++i]);
		;
	out = ft_calloc(i + 2, sizeof(char *));
	if (!out)
	{
		free_split(cmd->args);
		return ;
	}
	out[0] = ft_strdup(cmd->cmd);
	i = -1;
	while (cmd->args[++i] && out)
	{
		out[i + 1] = ft_strdup(cmd->args[i]);
		if (!out[i + 1])
		{
			free_split_rev(out, i + 1);
			out = NULL;
		}
	}
	free_split(cmd->args);
	cmd->args = out;
}

void	get_all_args(t_data *data)
{
	t_cmd	*ptr;
	
	ptr = data->cmd;
	while (ptr)
	{
		if (ptr->cmd)
		{
			if (!ptr->args)
				ptr->args = ft_split(ptr->cmd, '\0');
			else
				get_all_args_sub(ptr);
			if (!ptr->args)
				ft_exit(data, "malloc");
		}
		ptr = ptr->next;
	}
}

void	executer(t_data *data)
{

	if (!check_files(data))
		return ;
	if (!check_binaries(data))
		return ;
	get_all_args(data);
	
	t_cmd	*ptr;

	ptr = data->cmd;
	if (!ptr->next && !ft_strcmp("exit", ptr->cmd))
		bi_exit(data, ptr->args);
	// print_cmds(ptr);
	while (ptr)
	{
		if (!ft_strcmp("echo", ptr->cmd))
			data->ret = bi_echo(ptr);
		else if (!ft_strcmp("cd", ptr->cmd))
			data->ret = bi_cd(data, ptr);
		else if (!ft_strcmp("pwd", ptr->cmd))
			bi_pwd(data->env);
		else if (!ft_strcmp("export", ptr->cmd))
			data->ret = bi_export(data, ptr);
		else if (!ft_strcmp("unset", ptr->cmd))
			data->ret = bi_unset(data, ptr);
		else if (!ft_strcmp("env", ptr->cmd))
			bi_env(data);
		else
		{
			int pid = fork();
			if (pid == -1)
				ft_exit(data, "fork");
			if (!pid)
			{
				execve(ptr->cmd, ptr->args, data->env);
				printf("failed\n");
				exit(0);
				
			}
			else
				wait(NULL);
		}
		ptr = ptr->next;
	}
}
