/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dubug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:36:40 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/28 12:33:00 by dvavryn          ###   ########.fr       */
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

void	print_redirs(t_redir *redirs)
{
	t_redir	*ptr;

	ptr = redirs;
	if (!ptr)
	{
		printf("\tREDIRS:   NONE\n");
		return ;
	}
	printf("\tREDIRS:  ");
	while (ptr)
	{
		if (ptr->type == R_IN)
			printf(" [< %s]", ptr->filename);
		if (ptr->type == R_OUT)
			printf(" [> %s]", ptr->filename);
		if (ptr->type == R_APPEND)
			printf(" [>> %s]", ptr->filename);
		ptr = ptr->next;
	}
	printf("\n");
}

void	print_cmds(t_cmd *cmd)
{
	t_cmd	*ptr;
	size_t	i;
	ssize_t	j;
	
	ptr = cmd;
	i = 0;
	while (ptr)
	{
		printf("CMD [%ld]:\n", i);
		if (!ptr->cmd)
			printf("\tCMD:      NONE\n");
		else
			printf("\tCMD:      %s\n", ptr->cmd);
		j = -1;
		if (ptr->args)
		{
			printf("\tARGS:    ");
			while (ptr->args[++j])
				printf(" [%s]", ptr->args[j]);
			printf("\n");
		}
		else
			printf("\tARGS:     NONE\n");
		printf("\tPIPE-IN: ");
		if (ptr->pipe_in == 1)
			printf(" YES\n");
		else
			printf(" NO\n");
		printf("\tPIPE-OUT:");
		if (ptr->pipe_out == 1)
			printf(" YES\n");
		else
			printf(" NO\n");
		print_redirs(ptr->redirs);
		i++;
		ptr = ptr->next;
	}
}