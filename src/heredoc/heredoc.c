/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:21:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/01 16:55:46 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_print_heredoc(int fd)
{
	char	*line;

	if (fd == -1)
		return (ft_perror(MS "error: open read"));
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			printf("%s", line);
		line = get_next_line(fd);
	}
	if (unlink("tmp.txt") == -1)
		ft_perror(MS "error: unlink");
}

static void	ms_heredoc_execute(t_token *heredoc)
{
	char	*line;
	char	*end;
	int		fd;

	end = heredoc->value;
	fd = open("tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_perror(MS "error: create write"));
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!strcmp(line, end))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	heredoc->heredoc_fd = fd;
	// ms_print_heredoc(fd);
}

void	ms_heredoc(t_data *data)
{
	t_token	*curr;

	if (!data->token)
		return ;
	curr = data->token;
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC)
			ms_heredoc_execute(curr);
		curr = curr->next;
	}
}
