/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:27:06 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 16:58:45 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	write_to_heredoc(int fd, char *input)
{
	ssize_t	i;

	i = -1;
	i = write(fd, input, ft_strlen(input));
	free(input);
	if (i == -1)
		close(fd);
	return (i);
}

int	get_heredoc(t_data *data, char **lim)
{
	int			fd;
	char		*name;
	char		*input;

	name = get_heredoc_name();
	if (!name)
		return (-1);
	fd = open(name, O_CREAT | O_WRONLY, 0600);
	if (fd == -1)
		return (perror("open"), 0);
	input = get_heredoc_input(data, *lim);
	if (!input)
		return (close(fd), unlink(name), free(name), 0);
	if (write_to_heredoc(fd, input) == -1)
		return (unlink(name), free(name), 0);
	close(fd);
	free(*lim);
	*lim = name;
	return (1);
}
