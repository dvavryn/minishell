/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:37:30 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 17:00:39 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not leak free yet
char	*get_heredoc_input(t_data *data, char *lim)
{
	char	*buf;
	char	*tmp;
	char	*out;
	char	*clean_lim;

	clean_lim = clean_hd(lim);
	if (!clean_lim)
		ft_exit(data, "memory allocation");
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			printf("minishell: warning: here-document at line %ld "
				"delimited by end-of-file (wanted `%s`)\n", data->line, lim);
			break ;
		}
		if (!ft_strcmp(buf, clean_lim))
		{
			free(buf);
			break ;
		}
		tmp = out;
		out = ft_strjoin_endl(out, buf);
		free(tmp);
		free(buf);
		if (!out)
			return (free(clean_lim), NULL);
	}
	if (!ft_strchr(lim, '\'') && !ft_strchr(lim, '\"'))
	{
		tmp = out;
		out = expand_heredoc(data, out);
		free(tmp);
	}
	free(clean_lim);
	if (!out)
		return (NULL);
	return (out);
}
