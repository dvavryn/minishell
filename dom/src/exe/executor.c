/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:58:26 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 17:10:11 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_sub2(char **arr, char *s)
{
	ssize_t	i;
	char	*out;

	i = -1;
	while (arr[++i])
	{
		if (!access(arr[i], F_OK | X_OK))
		{
			out = ft_strdup(arr[i]);
			break ;
		}
	}
	if (!arr[i])
		out = ft_strdup(s);
	free_split(arr);
	if (!out)
		return (NULL);
	return (out);
}

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
	return (get_path_sub2(arr, s));
}

int	get_path(t_data *data, t_cmd *cmd)
{
	char	*ptr;
	char	*path;

	if (!cmd->cmd)
		return (1);
	ptr = cmd->cmd;
	if (ft_strchr(ptr, '/'))
		path = ft_strdup(ptr);
	else
		path = get_path_sub(data, ptr);
	if (!path)
		ft_exit(data, "malloc");
	cmd->cmd = path;
	free(ptr);
	if (access(cmd->cmd, F_OK | X_OK))
	{
		perror(cmd->cmd);
		data->ret = 127;
		return (0);
	}
	return (1);
}

int	cmd_not_found(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, ": command not found\n", 20);
	return (0);
}

int	check_binaries(t_data *data)
{
	t_cmd	*ptr;
	int		i;

	ptr = data->cmd;
	while (ptr)
	{
		if (ptr->cmd)
		{
			i = 0;
			while (ptr->cmd[i] && !ft_isalnum(ptr->cmd[i]))
				i++;
			if (!ptr->cmd[i])
				return (cmd_not_found(ptr->cmd));
		}
		// if (ptr->cmd && !isbuiltin(ptr->cmd))
		if (ptr->cmd)
			if (!get_path(data, ptr))
				return (0);
		ptr = ptr->next;
	}
	return (1);
}

int	check_files(t_data *data)
{
	t_cmd	*ptr;
	int		fd;

	ptr = data->cmd;
	while (ptr)
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
		}
		ptr = ptr->next;
	}
	return (1);
}

void	get_all_args_sub(t_cmd *cmd)
{
	char	**out;
	ssize_t	i;

	i = 0;
	while (cmd->args[++i])
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

int	wait_childs(t_data *data)
{
	t_cmd	*ptr;

	ptr = data->cmd;
	while (ptr)
	{
		wait(NULL);
		ptr = ptr->next;
	}
	return (0);
}

void	dups_files(t_data *data, t_cmd *cmd)
{
	int	fd;

	if (cmd->redir_in)
	{
		fd = open(cmd->file_in, O_RDONLY);
		if (fd == -1)
			ft_exit(data, "open");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->redir_out)
	{
		if (cmd->redir_out == R_OUT)
			fd = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->redir_out == R_APPEND)
			fd = open (cmd->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_exit(data, "open");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	dups_pipes(int pipe[2][2], size_t i, size_t count_cmds)
{
	if (i > 0)
		dup2(pipe[(i + 1) % 2][0], STDIN_FILENO);
	if (i < count_cmds - 1)
		dup2(pipe[i % 2][1], STDOUT_FILENO);
	if (pipe[0][0] != -1)
		close(pipe[0][0]);
	if (pipe[0][1] != -1)
		close(pipe[0][1]);
	if (pipe[1][0] != -1)
		close(pipe[1][0]);
	if (pipe[1][1] != -1)
		close(pipe[1][1]);
}

size_t	get_count_cmds(t_cmd *cmd)
{
	t_cmd	*ptr;
	size_t	out;

	out = 0;
	ptr = cmd;
	while (ptr)
	{
		out++;
		ptr = ptr->next;
	}
	return (out);
}

void	my_execve_close(int pipes[2][2], size_t i)
{
	if (i > 0)
	{
		close(pipes[(i + 1) % 2][0]);
		close(pipes[(i + 1) % 2][1]);
	}
}

void	my_execve(t_data *data, t_cmd *cmd, int pipes[2][2], size_t	i)
{
	int				pid;
	size_t			count_cmds;

	count_cmds = get_count_cmds(data->cmd);
	if (i < count_cmds - 1)
	{
		if (pipe(pipes[i % 2]))
			ft_exit(data, "pipe");
	}
	pid = fork();
	if (pid == -1)
		ft_exit(data, "fork");
	if (!pid)
	{
		dups_pipes(pipes, i, count_cmds);
		dups_files(data, cmd);
		execve(cmd->args[0], cmd->args, data->env);
		ft_exit(data, "execve");
	}
	else
		my_execve_close(pipes, i);
}

void	executer_init_pipes(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

void handle_builtin()
{
	
}

void	executer(t_data *data)
{
	t_cmd	*ptr;
	int		pipes[2][2];
	size_t	i;

	executer_init_pipes(pipes);
	if (!check_files(data))
		return ;
	if (!check_binaries(data))
		return ;
	get_all_args(data);
	ptr = data->cmd;
	i = 0;
	while (ptr)
	{
		if (ptr->cmd)
		{
			// if (isbuiltin(ptr->cmd))
			// 	handle_builtin(data, ptr, );
			// else
				my_execve(data, ptr, pipes, i);
		}
		ptr = ptr->next;
		i++;
	}
	while (wait(NULL) > 0)
		;
}
