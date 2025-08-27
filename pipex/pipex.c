/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:10 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/27 12:22:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (!pid)
	{
		if (execve(cmd[0], cmd, envp))
		{
			printf("failed to execute\n");
			return (1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	**path;
	char	*executable;
	int		path_type;
	ssize_t	i;

	if (!argv[1] || !argv[1][0])
	{
		write(2, "Missing executable\n", 19);
		return (1);
	}
	cmd = get_cmd(argc, argv);
	if (!cmd)
		return (1);
	path_type = get_path_type(cmd[0]);
	if (path_type == RELATIVE)
		executable = get_relative_path(argv[1]);
	else if (path_type == ABSOLUTE)
		executable = ft_strdup(argv[1]);
	else if (path_type == SEARCH)
	{
		if (cmd[0])
			path = get_path(envp, argv[1]);
		if (!path)
			return (free_split(cmd), 1);
		executable = get_access(path);
	}
	if (!executable)
		return (free_split(cmd), 1);
	free(cmd[0]);
	cmd[0] = executable;
	if (test_permissions(cmd[0]))
		return (free_split(cmd), 1);
	printf("The command is:");
	i = -1;
	while (cmd[++i])
		printf(" %s", cmd[i]);
	printf("\n");
	execute(cmd, envp);
	free_split(cmd);
}
