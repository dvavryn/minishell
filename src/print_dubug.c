/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dubug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:36:40 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 17:13:11 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*ptr;
	char	*type[7];

	type[0] = "TOKEN_NONE";
	type[1] = "TOKEN_WORD";
	type[2] = "TOKEN_PIPE";
	type[3] = "TOKEN_REDIR";
	type[4] = "TOKEN_TO_EXPAND";
	type[5] = "TOKEN_QUOTE";
	type[6] = "TOKEN_HEREDOC";
	ptr = tokens;
	while (ptr)
	{
		printf("Token: '%s', Type: %s\n", ptr->value, type[ptr->type]);
		ptr = ptr->next;
	}
}

void	print_cmds(t_cmd *ptr)
{
	t_cmd	*cmd;
	size_t	i;
	ssize_t	j;

	cmd = ptr;
	i = 0;
	while (cmd)
	{
		printf("CMD [#%zu]\n", i);
		if (cmd->pipe_in)
			printf("\tPIPE-IN: YES\n");
		else
			printf("\tPIPE-IN: NO\n");
		if (cmd->redir_in == R_IN)
			printf("\tREDIR-IN: %s\n", cmd->file_in);
		else if (cmd->redir_in == R_HEREDOC)
			printf("\tREDIR-IN: HD %s\n", cmd->file_in);
		else
			printf("\tREDIR-IN: NO\n");
		printf("\tCMD: %s\n", cmd->cmd);
		j = -1;
		printf("\tARGS: ");
		if (cmd->args)
		{
			while (cmd->args[++j])
				printf("[%s] ", cmd->args[j]);
			printf("\n");
		}
		else
			printf("none\n");
		if (cmd->redir_out == R_OUT)
			printf("\tREDIR-OUT: %s\n", cmd->file_out);
		else if (cmd->redir_out == R_APPEND)
			printf("\tREDIR-OUT: APPEND %s\n", cmd->file_out);
		else
			printf("\tREDIR-OUT: NO\n");
		if (cmd->pipe_out)
			printf("\tPIPE-OUT: YES\n");
		else
			printf("\tPIPE-OUT: NO\n");
		cmd = cmd->next;
		i++;
	}
}