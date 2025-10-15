/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:37:30 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 12:30:03 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_flag = 0;

void	heredoc_signal(int sig)
{
	(void)sig;
	g_flag = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

// not leak free yet
char	*get_heredoc_input(t_data *data, char *lim)
{
	char	*buf;
	char	*tmp;
	char	*out;
	char	*clean_lim;

	signal(SIGINT, heredoc_signal);
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
		if (g_flag == 1)
		{
			g_flag = 0;
			free(buf);
			break;
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
