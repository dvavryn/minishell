/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:10 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/26 22:20:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void print_cmd(t_cmd cmd)
{
	ssize_t	i;
	
	printf("IN MODE:\t");
	if (!cmd.in_mode)
		printf("STDIN\n");
	else if (cmd.in_mode == 1)
		printf("O_RDONLY\n");
	else if (cmd.in_mode == 2)
		printf("HEREDOC");
	if (!cmd.infile)
		printf("INFILE:\tno infile\n");
	else if (cmd.infile && cmd.in_mode == 1)
		printf("INFILE PATH:\t%s\n", cmd.infile);
	else if (cmd.infile && cmd.in_mode == 2)
		printf("HEREDOC LIMITER:\t\"%s\"\n", cmd.infile);
	if (!cmd.cmd || !*cmd.cmd)
		printf("NO CMD\n");
	else
	{
		i = -1;
		while (cmd.cmd[++i])
			printf("LINE %li CMD: %s", i, cmd.cmd[i]);
	}
	printf("OUTMODE:\t");
	if (!cmd.out_mode)
		printf("STDOUT\n");
	else if (cmd.out_mode == 1)
		printf("O_WRONLY\n");
	else if (cmd.out_mode == 2)
		printf("O_APPEND\n");
	printf("OUTFILE:\t");
	if (!cmd.outfile)
		printf("no outfile\n");
	else
		printf("%s\n", cmd.outfile);
		
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	t_cmd	cmd;
	ft_bzero(&cmd, sizeof(t_cmd));
	cmd = put_in_here();
	print_cmd(cmd);
	if (!check_cmd(cmd))
		return (1);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**path;
// 	char	*executable;
// 	int		path_type;
// 	ssize_t	i;

// 	if (!argv[1] || !argv[1][0])
// 	{
// 		write(2, "Missing executable\n", 19);
// 		return (1);
// 	}
// 	path_type = get_path_type(argv[1]);
// 	if (path_type == RELATIVE)
// 		executable = get_relative_path(argv[1]);
// 	else if (path_type == ABSOLUTE)
// 		executable = ft_strdup(argv[1]);
// 	else if (path_type == SEARCH)
// 	{
// 		if (argv[1])
// 			path = get_path(envp, argv[1]);
// 		if (!path)
// 			return (1);
// 		executable = get_access(path);
// 	}
// 	if (!executable)
// 		return (1);
// 	if (test_permissions(executable))
// 		return (1);
// 	printf("The executable is: %s\n", executable);
// 	free(executable);
// }
