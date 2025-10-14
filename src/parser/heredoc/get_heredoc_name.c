/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:30:32 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/14 18:17:50 by dvavryn          ###   ########.fr       */
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
	int		fd;
	size_t	i;
	char	buffer[50];
	char	*filename;

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
	printf("%s\n", filename);
	filename = ft_strjoin("/tmp/", filename);
	close(fd);
	return (filename);
}
