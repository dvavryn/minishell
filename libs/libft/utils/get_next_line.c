/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/07/21 10:41:44 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*update_store(char *store)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
		return (free(store), NULL);
	tmp = malloc(ft_strlen(store + i + 1) + 1);
	if (!tmp)
		return (free(store), NULL);
	i++;
	j = 0;
	while (store[i])
		tmp[j++] = store[i++];
	tmp[j] = '\0';
	free(store);
	return (tmp);
}

static char	*fill_line(char *store)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	line = malloc(i + (store[i] == '\n') + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = store[j];
		j++;
	}
	if (store[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static int	fill_store(int fd, char **store)
{
	char	buffer[BUFFER_SIZE + 1];
	int		size;
	char	*tmp;

	size = 1;
	if (!*store)
		*store = ft_strdup("");
	while (!ft_strchr(*store, '\n') && size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size < 0)
			return (-1);
		buffer[size] = '\0';
		tmp = ft_strjoin(*store, buffer);
		if (!tmp)
		{
			free(*store);
			*store = NULL;
			return (-1);
		}
		free(*store);
		*store = tmp;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	check = fill_store(fd, &store);
	if (check < 0 || !store || *store == '\0')
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	line = fill_line(store);
	if (!line)
		return (free(store), NULL);
	store = update_store(store);
	return (line);
}
