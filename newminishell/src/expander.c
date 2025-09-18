// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expander.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/08 20:16:39 by dvavryn           #+#    #+#             */
// /*   Updated: 2025/09/18 12:11:57 by dvavryn          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO
// // TODOTODOTODOTODOTODOTODO

// // void	jump_quotes(char *s, int c, size_t *i)
// // {
// // 	while (ptr[i] && ptr[i])
// // }

// char	*expand_str(t_data *data, char *s)
// {
// 	size_t	i;
// 	char	*out = NULL;
// 	char	*buf[2];
// 	char	*ptr;

// 	i = 0;
// 	ptr = s;
// 	out = ft_strdup("");
// 	while (s[i])
// 	{
// 		i = 0;
// 		while (ptr[i] && ptr[i] != '$')
// 		{
// 			if (ptr[i] == '\'')
// 				jump_quotes(ptr, ptr[i], &i);
// 			i++;
// 		}
// 		buf[0] = ft_substr(ptr, 0, i);
// 		if (!buf[0])
// 		{
// 			free(out);
// 			ft_exit(data, "malloc");
// 		}
// 		buf[1] = ft_strjoin(out, buf[0]);
// 		free(buf[0]);
// 		if (!buf[1])
// 			ft_exit(data, "maloc");
// 		free(out);
// 		out = buf[1];
// 		ptr += i;
// 	}
// 	if (!out)
// 		ft_exit(data, "malloc");
// 	return (out);
// }

// void	expand(t_data *data, t_cmd *cmd)
// {
// 	ssize_t	i;

// 	if (!ft_strchr(cmd->cmd, '\''))
// 		cmd->cmd = expand_str(data, cmd->cmd);
// 	if (cmd->redir_in == R_IN && !ft_strchr(cmd->file_in, '\''))
// 		cmd->file_in = expand_str(data, cmd->file_in);
// 	if (cmd->redir_out)
// 		cmd->file_out = expand_str(data, cmd->file_out);
// 	i = -1;
// 	while (cmd->args[++i])
// 	{
// 		if (!ft_strchr(cmd->args[i], '\''))
// 			cmd->args[i] = expand_str(data, cmd->args[i]);
// 	}
// }

// int	expander(t_data *data)
// {
// 	t_cmd	*ptr;

// 	ptr = data->cmd;
// 	while (ptr)
// 	{
// 		expand(data, ptr);
// 		ptr = ptr->next;
// 	}
// 	return (0);
// }
