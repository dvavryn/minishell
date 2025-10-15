/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:37:30 by dvavryn           #+#    #+#             */
/*   Updated: 2025/10/15 15:34:19 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_flag = 0;

static void	heredoc_signal(int sig)
{
	char	nl;

	nl = 32;
	(void)sig;
	g_flag = 1;
	rl_done = 1;
	printf("> ^C\n");
	ioctl(STDIN_FILENO, TIOCSTI, &nl);
}

static int	manage_heredoc_input(t_data *data, char **out, char *clean_lim,
	char *lim)
{
	char	*buf;
	char	*tmp;

	if (g_flag == 1)
	{
		g_flag = 0;
		data->hd_quit = 1;
		return (2);
	}
	buf = readline("> ");
	if (!buf)
	{
		printf("minishell: warning: here-document at line %ld "
			"delimited by end-of-file (wanted `%s`)\n", data->line, lim);
		return (2);
	}
	if (!ft_strcmp(buf, clean_lim))
		return (free(buf), 2);
	tmp = *out;
	*out = ft_strjoin_endl(*out, buf);
	return (free(tmp), free(buf), 0);
}

char	*get_heredoc_input(t_data *data, char *lim, char *out)
{
	char	*tmp;
	char	*clean_lim;

	signal(SIGINT, heredoc_signal);
	clean_lim = clean_hd(lim);
	if (!clean_lim)
		return (free(out), ft_exit(data, "memory allocation"), NULL);
	if (!out)
		return (NULL);
	while (1)
	{
		if ((manage_heredoc_input(data, &out, clean_lim, lim)) == 2)
			break ;
		if (!out)
			return (free(clean_lim), NULL);
	}
	if (!ft_strchr(lim, '\'') && !ft_strchr(lim, '\"'))
	{
		tmp = out;
		out = expand_heredoc(data, out);
		free(tmp);
	}
	if (!out)
		return (free(clean_lim), NULL);
	return (free(clean_lim), out);
}
