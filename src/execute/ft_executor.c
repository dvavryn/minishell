/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:40:23 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/01 12:49:10 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exe_data
{
	t_token	*tokens;
	char	**envp;
}	t_exe_data;

void	ft_executor(t_token *tokens, char **envp)
{
	t_exe_data	data;

	ft_bzero(&data, sizeof(t_exe_data));
	data.tokens = tokens;
	data.envp = envp;
	while (data.tokens)
	{
		if (0)
			;
		else
			printf("%s ", data.tokens->value);
		data.tokens = data.tokens->next;
	}
	printf("\n");
	(void)tokens;
}
