// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_executor.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/01 14:48:43 by dvavryn           #+#    #+#             */
// /*   Updated: 2025/09/01 16:43:25 by dvavryn          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// t_cmd	*add_cmd_empty()
// {
// 	t_cmd	*out;

// 	out = ft_calloc(1, sizeof(t_cmd));
// 	if (!out)
// 		return (NULL);
// 	out->infile = -1;
// 	out->heredoc = -1;
// 	out->cmd = NULL;
// 	out->outfile = -1;
// 	out->ret = -1;
// 	out->next = NULL;
// 	out->piped = 0;
// 	return (out);
// }

// char	**add_split(char **split, char *val)
// {
// 	char **out;
// 	ssize_t	i;

// 	i = -1;
// 	while (split[++i])
// 		;
// 	out = ft_calloc(i + 2, sizeof(char *));
// 	if (!out)
// 		return (NULL);
// 	i = 0;
// 	while (split[i])
// 	{
// 		out[i] = split[i];
// 		i++;
// 	}
// 	out[i] = ft_strdup(val);
// 	if (!out[i])
// 	{
// 		free(out);
// 		return (NULL);
// 	}
// 	return (out);
// }

// int	get_cmds(t_cmd *cmds, t_token *token)
// {
// 	t_token	*ptr_t;
// 	t_cmd	*ptr_c;
	
// 	ptr_t = token;
// 	cmds = add_cmd_empty();
// 	ptr_c = cmds;
// 	while (ptr_t)
// 	{
// 		if (ptr_t->type == TOKEN_REDIR_IN)
// 		{
// 			if (ptr_c->infile != -1)
// 			{
// 				close(ptr_c->infile);

// 			}
// 			ptr_c->infile = open(ptr_t->value, O_RDONLY);
// 		}
// 		else if (ptr_t->type == TOKEN_APPEND_OUT)
// 			ptr_c->heredoc = ptr_t->heredoc_fd;
// 		else if (ptr_t->type == TOKEN_REDIR_OUT)
// 			ptr_c->outfile = open(ptr_t->value, O_WRONLY | O_CREAT | O_TRUNC | 0666);
// 		else if (ptr_t->type == TOKEN_APPEND_OUT)
// 			ptr_c->outfile = open(ptr_t->value, O_APPEND | O_CREAT | 0666);
// 		else if (ptr_t->type == TOKEN_WORD)
// 			ptr_c->cmd = add_split(ptr_c->cmd, ptr_t->value);
// 		else if (ptr_t->type == TOKEN_PIPE)
// 		{
// 			ptr_c->next = add_cmd_empty();
// 			ptr_t = ptr_t->next;
// 			ptr_c = ptr_c->next;
// 			ptr_c->piped = 1;
// 		}
// 		ptr_t = ptr_t->next;
// 	}
// 	return (0);
// }

// void print_cmds(t_cmd *cmds)
// {
// 	t_cmd *ptr = cmds;
// 	char **arr;
// 	int i = 0;
	
// 	while (ptr)
// 	{
// 		printf("cmd[%i]\n", i++);
// 		if (ptr->infile != -1)
// 			printf("infile: %i\n", ptr->infile);
// 		if (ptr->heredoc != -1)
// 			printf("heredoc: %i\n", ptr->heredoc);
// 		if (ptr->cmd)
// 		{
// 			arr = ptr->cmd;
// 			printf("cmd: ");
// 			while (*arr)
// 			{
// 				printf("%s ", *arr);
// 				arr++;
// 			}
// 			printf("\n");
// 		}
// 		if (ptr->outfile)
// 			printf("outfile: %i\n", ptr->outfile);
// 		if (ptr->next)
// 			printf("piped into\n");
// 		else
// 			printf("end\n");
// 	}
// }

// int	ft_executor(t_data *data)
// {
// 	t_cmd	*cmds;
// 	(void)data;
	
// 	cmds = NULL;
// 	if (get_cmds(cmds, data->token))
// 		;
// 	print_cmds(cmds);
// 	// while (cmds)
// 	// {
// 	// 	if (cmds->infile != -1)
// 	// 		close(cmds->infile);
// 	// 	if (cmds->outfile != -1)
// 	// 		close(cmds->outfile);
// 	// 	if (cmds->heredoc != -1)
// 	// 		close(cmds->heredoc);
// 	// 	if (cmds->cmd)
// 	// 		free_split(cmds->cmd);
// 	// 	cmds = cmds->next;
// 	// }
// 	return (0);
// }