/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:30:32 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 15:50:36 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_char(char *buffer)
{
	size_t	i;

	i = -1;
	while (buffer[++i])
	{
		if (ft_isalnum(buffer[i]))
			return (buffer[i]);
	}
	return (0);
}

char	*get_heredoc_name(void)
{
	size_t	i;
	int		fd;
	char	buffer[50];
	char	*filename;
	char	*tmp;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	filename = malloc(sizeof(char) * 16);
	if (!filename)
		return (close(fd), NULL);
	while ((read(fd, buffer, 50)) > 0)
	{
		if (i == 15)
			break ;
		filename[i] = get_char(buffer);
		if (filename[i])
			i++;
	}
	filename[i] = '\0';
	tmp = filename;
	filename = ft_strjoin("/tmp/", filename);
	return (free(tmp), close(fd), filename);
}
