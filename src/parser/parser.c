/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:03:33 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 12:28:25 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_validity(t_data *data)
{
	t_token	*ptr;

	ptr = data->tokens;
	if (ptr->type == TOKEN_PIPE)
		return (ms_perror("MS syntax: command can't start with pipe"), 0);
	while (ptr)
	{
		if (!(ptr->type == TOKEN_HEREDOC || ptr->type == TOKEN_PIPE
				|| ptr->type == TOKEN_REDIR) && !isclosed(ptr->value))
			return (ms_perror("MS parser: unclosed quotes"), 0);
		if (ptr->type != TOKEN_QUOTE && (ft_strchr(ptr->value, '\\')
				|| ft_strchr(ptr->value, ';') /* '&' '||' '&&' * ( ) [ ] { } /)) */ ))
			return (ms_perror("MS syntax: cannot be interpreted"), 0);
		if ((ptr->type == TOKEN_PIPE && !ptr->next)
			|| ((ptr->type == TOKEN_REDIR || ptr->type == TOKEN_HEREDOC)
				&& !ptr->next))
			return (ms_perror("MS syntax: next to special character"), 0);
		ptr = ptr->next;
	}
	return (1);
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
