/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:05:08 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/25 14:24:11 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	ssize_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

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

char	*generate_name(void)
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
	filename = ft_strjoin("/tmp/", filename);
	close(fd);
	return (filename);
}
