/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:22:36 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/19 13:04:51 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isclosed(char *s)
{
	size_t	i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (s[i] != c)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_validity(t_data *data)
{
	t_token	*ptr;

	ptr = data->tokens;
	if (ptr->type == TOKEN_PIPE)
		return (ft_perror("syntax error: command can't start with pipe"), 0);
	while (ptr)
	{
		if (!(ptr->type == TOKEN_HEREDOC || ptr->type == TOKEN_PIPE
				|| ptr->type == TOKEN_REDIR) && !isclosed(ptr->value))
			return (ft_perror("parser: unclosed quotes"), 0);
		if (ptr->type != TOKEN_QUOTE && (ft_strchr(ptr->value, '\\')
				|| ft_strchr(ptr->value, ';')))
			return (ft_perror
				("syntax error: ';' and '\\' cannot be interpreted"), 0);
		if ((ptr->type == TOKEN_PIPE && !ptr->next)
			|| ((ptr->type == TOKEN_REDIR || ptr->type == TOKEN_HEREDOC)
				&& !ptr->next))
			return (ft_perror("syntax error: next to special character"), 0);
		ptr = ptr->next;
	}
	return (1);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*out;

	out = ft_calloc(1, sizeof(t_cmd));
	if (!out)
		return (NULL);
	out->fd_in = -1;
	out->fd_out = -1;
	return (out);
}

void	add_cmd(t_data *data)
{
	t_cmd	*ptr;

	if (!data->cmd)
	{
		data->cmd = new_cmd();
		if (!data->cmd)
			ft_exit(data, "malloc");
	}
	else
	{
		ptr = data->cmd;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_cmd();
		if (!ptr->next)
			ft_exit(data, "malloc");
		ptr->next->next = NULL;
	}
}

size_t	get_split_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**split_copy(char **arr)
{
	char	**out;
	ssize_t	i;

	out = ft_calloc(get_split_size(arr) + 2, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		out[i] = ft_strdup(arr[i]);
		if (!out[i])
		{
			while (--i >= 0)
				free(out[i]);
			free(out);
			return (NULL);
		}
	}
	return (out);
}

void	split_join_sub(t_data *data, t_cmd **cmd, char *value)
{
	(*cmd)->args = ft_split(value, '\0');
	if (!(*cmd)->args)
		ft_exit(data, "malloc");
}

void	split_join(t_data *data, t_cmd *cmd, char *value)
{
	char	**out;
	char	*buf;
	size_t	i;

	if (!cmd->args)
		split_join_sub(data, &cmd, value);
	else
	{
		buf = ft_strdup(value);
		if (!buf)
			ft_exit(data, "malloc");
		out = split_copy(cmd->args);
		if (!out)
		{
			free(buf);
			ft_exit(data, "malloc");
		}
		i = 0;
		while (out[i])
			i++;
		out[i] = buf;
		cmd->args = out;
	}
}

char	*get_heredoc_name(void)
{
	static int	num;
	char		*out;
	char		*buf;

	buf = ft_itoa(num);
	if (!buf)
		return (NULL);
	out = ft_strjoin(".heredoc", buf);
	free(buf);
	if (!out)
		return (NULL);
	return (out);
}

void	clean_hd_sub(char *in, char **out, size_t i, size_t j)
{
	size_t	len;
	char	q;

	len = ft_strlen(in);
	q = 0;
	while (i < len)
	{
		if (!q)
		{
			if (in[i] == '"' || in[i] == '\'')
				q = in[i++];
			else
				(*out)[j++] = in[i++];
		}
		else
		{
			if (in[i] == q)
			{
				q = 0;
				i++;
			}
			else
				(*out)[j++] = in[i++];
		}
	}
}

char	*clean_hd(char *in)
{
	char	*out;

	out = ft_calloc(1, ft_strlen(in) + 1);
	if (!out)
		return (NULL);
	clean_hd_sub(in, &out, 0, 0);
	return (out);
}

char	*expand_heredoc_sub_word(t_data *data, char *ptr, size_t *i)
{
	char	*var;
	char	c;
	char	*out;

	c = ptr[*i];
	ptr[*i] = 0;
	var = ft_strdup(&ptr[1]);
	ptr[*i] = c;
	if (!var)
		return (NULL);
	if (!ms_getenv(data->env, var))
		out = ft_strdup("");
	else
		out = ft_strdup(ms_getenv(data->env, var));
	free(var);
	if (!out)
		return (NULL);
	return (out);
}

char	*expand_heredoc(t_data *data, char *input)
{
	char	*out;
	char	*buf[2];
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = input;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (*ptr)
	{
		i = 0;
		while (ptr[i] && ptr[i] != '$')
			i++;
		buf[0] = ft_substr(ptr, 0, i);
		if (!buf[0])
			return (free(out), NULL);
		buf[1] = out;
		out = ft_strjoin(out, buf[0]);
		free(buf[0]);
		free(buf[1]);
		if (!out)
			return (NULL);
		ptr += i;
		if (*ptr == '$')
		{
			i = 1;
			while (ptr[i] && ft_isalnum(ptr[i]))
				i++;
			buf[0] = expand_heredoc_sub_word(data, ptr, &i);
			if (!buf[0])
				return (free(out), NULL);
			buf[1] = out;
			out = ft_strjoin(out, buf[0]);
			free(buf[0]);
			free(buf[1]);
			if (!out)
				return (NULL);
			ptr += i;
		}
	}
	return (out);
}

char	*ft_strjoin_endl(char *s1, char *s2)
{
	char	*out;
	ssize_t	i;
	ssize_t	j;

	out = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!out)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		out[++j] = s1[i];
	i = -1;
	while (s2[++i])
		out[++j] = s2[i];
	out[++j] = '\n';
	out[++j] = 0;
	return (out);
}

// not leak free yet
char	*get_heredoc_input(t_data *data, char *lim)
{
	char	*buf;
	char	*tmp;
	char	*out;
	char	*clean_lim;

	clean_lim = clean_hd(lim);
	if (!clean_lim)
		ft_exit(data, "malloc");
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

ssize_t	write_to_heredoc(int fd, char *input)
{
	ssize_t	i;

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
		return (perror("open"), -1);
	input = get_heredoc_input(data, *lim);
	if (!input)
		return (close(fd), unlink(name), free(name), -1);
	if (write_to_heredoc(fd, input) == -1)
		return (unlink(name), -1);
	free(*lim);
	*lim = name;
	return (fd);
}

void	add_cmd_pipe(t_data *data, t_cmd **cmd)
{
	add_cmd(data);
	(*cmd)->pipe_out = 1;
	*cmd = (*cmd)->next;
	(*cmd)->pipe_in = 1;
}

void	add_cmd_word(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if (!(*cmd)->cmd)
	{
		(*cmd)->cmd = ft_strdup(ptr->value);
		if (!(*cmd)->cmd)
			ft_exit(data, "malloc");
	}
	else
		split_join(data, *cmd, ptr->value);
}

void	add_cmd_redir_in(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if ((*cmd)->redir_in > 0)
		close((*cmd)->fd_in);
	if (ptr->value[0] != ptr->value[1])
		(*cmd)->redir_in = R_IN;
	else
		(*cmd)->redir_in = R_HEREDOC;
	if ((*cmd)->file_in)
		free((*cmd)->file_in);
	(*cmd)->file_in = ft_strdup(ptr->next->value);
	if (!(*cmd)->file_in)
		ft_exit(data, "malloc");
	if ((*cmd)->redir_in == R_HEREDOC)
	{
		(*cmd)->fd_in = get_heredoc(data, &(*cmd)->file_in);
		if ((*cmd)->fd_in == -1)
			ft_exit(data, "malloc");
	}
}

void	add_cmd_redir_out(t_data *data, t_token *ptr, t_cmd **cmd)
{
	if (ptr->value[0] != ptr->value[1])
		(*cmd)->redir_out = R_OUT;
	else
		(*cmd)->redir_out = R_APPEND;
	if ((*cmd)->file_out)
		free((*cmd)->file_out);
	(*cmd)->file_out = ft_strdup(ptr->next->value);
	if (!(*cmd)->file_out)
		ft_exit(data, "malloc");
}

void	get_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_token	*ptr;

	add_cmd(data);
	cmd = data->cmd;
	ptr = data->tokens;
	while (ptr)
	{
		if (ptr->type == TOKEN_PIPE)
			add_cmd_pipe(data, &cmd);
		else if (ptr->type == TOKEN_REDIR || ptr->type == TOKEN_HEREDOC)
		{
			if (!ft_strcmp(ptr->value, "<") || !ft_strcmp(ptr->value, "<<"))
				add_cmd_redir_in(data, ptr, &cmd);
			else
				add_cmd_redir_out(data, ptr, &cmd);
			ptr = ptr->next;
		}
		else
			add_cmd_word(data, ptr, &cmd);
		ptr = ptr->next;
	}
}

char	*cleanup_args_sub3(char *s, size_t *i)
{
	size_t	j;
	char	*out;

	j = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '\"')
		(*i)++;
	out = ft_substr(s, j, *i - j);
	if (!out)
		return (NULL);
	return (out);
}

char	*cleanup_args_sub2(char *s, size_t *i)
{
	size_t	j;
	char	c;
	char	*out;

	c = s[(*i)++];
	j = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] == c)
	{
		out = ft_substr(s, j, *i - j);
		(*i)++;
	}
	else
	{
		out = ft_substr(s, j - 1, ft_strlen(s) - j - 1);
		*i = ft_strlen(s);
	}
	if (!out)
		return (NULL);
	return (out);
}

char	*cleanup_args_sub(char *s)
{
	size_t	i;
	char	*out;
	char	*buf[2];

	i = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			buf[0] = cleanup_args_sub2(s, &i);
		else
			buf[0] = cleanup_args_sub3(s, &i);
		if (!buf[0])
			return (free(out), NULL);
		buf[1] = out;
		out = ft_strjoin(out, buf[0]);
		free(buf[0]);
		free(buf[1]);
		if (!out)
			return (NULL);
	}
	return (out);
}

void	cleanup_args(t_data *data)
{
	t_cmd	*ptr;
	ssize_t	i;
	char	*buf;

	ptr = data->cmd;
	while (ptr)
	{
		if (ptr->args)
		{
			i = -1;
			while (ptr->args[++i])
			{
				buf = cleanup_args_sub(ptr->args[i]);
				if (!buf)
					ft_exit(data, "malloc");
				free(ptr->args[i]);
				ptr->args[i] = buf;
			}
		}
		ptr = ptr->next;
	}
}

int	parser(t_data *data)
{
	if (!check_validity(data))
	{
		data->ret = 2;
		return (0);
	}
	get_cmd(data);
	cleanup_args(data);
	return (1);
}
