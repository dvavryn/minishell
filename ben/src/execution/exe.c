// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exe.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/01 15:51:56 by dvavryn           #+#    #+#             */
// /*   Updated: 2025/09/01 16:55:54 by dvavryn          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// t_cmd	*get_cmds(t_token *token)
// {
// 	(void)token;
// 	return (NULL);
// }

// int	execute_sub(t_cmd *cmd, int *fd)
// {
// 	int	pid;
// 	int dupe;

// 	if (pid == -1)
// 		return (-2);
// 	if (!pid)
// 	{
// 		if (cmd->piped)
// 			dup2(fd[0], STDIN_FILENO);	
// 		if (cmd->infile != -1)
// 			dup2(cmd->infile, STDIN_FILENO);
// 		if (cmd->heredoc != -1)
// 			dup2(cmd->heredoc, STDIN_FILENO);
// 		if (cmd->outfile != -1)
// 			dup2(cmd->outfile, STDOUT_FILENO);
// 		else if (cmd->next)
// 			dup2(fd[1], STDOUT_FILENO);
// 	}
// }

// void	execute(t_cmd *cmds)
// {
// 	t_cmd	*ptr;
// 	int		fd[2];

// 	if (pipe(fd))
// 		return ;
// 	ptr = cmds;
// 	while (ptr)
// 	{
// 		ptr = ptr->next;
// 	}
// }

// int	ft_executor(t_data *data)
// {
// 	t_cmd	*cmds;

// 	cmds = NULL;
// 	cmds = get_cmds(data->token);
// 	if (!cmds)
// 		return (1);
// 	execute(cmds);
// 	return (0);
// }`