/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:32 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 14:55:18 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	char	**env;
	t_token	*token;
	char	*input;
}	t_data;

char **copy_env(char **envp)
{
	char **out;
	ssize_t	i;
	i = -1;
	while (envp[++i])
		;
	out = ft_calloc(i + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		out[i] = ft_strdup(envp[i]);
		if (!out[i])
		{
			free_split(out);
			return (NULL);
		}
	}
	return (out);
}

int	get_data(t_data *data, char **envp)
{
	data->env = copy_env(envp);
	if (!data->env)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data	data;
	
	ft_bzero(&data, sizeof(t_data));
	if (get_data(&data, envp))
	{
		ft_perror("fucking shit doesnt work! it crashed\n");
		return (1);
	}
	while (1)
	{
		data.input = readline("minishell > ");
		if (!data.input)
		{
			printf("exit\n");
			exit(0);
		}
		else if (*data.input == 0)
		{
			free(data.input);
		}
		else
		{
			add_history(data.input);
			data.token = lex_input(data.input);
			if (data.token)
			{
				if (!ft_strncmp("exe", data.token->value, ft_strlen(data.token->value)))
				{
					printf("going into execution mode!\n");
					ft_executor(data.token->next, envp);
				}
				else
					print_tokens(data.token);
				free_tokens(data.token);
			}
		}
	}
}
