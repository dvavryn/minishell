/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:32 by bschwarz          #+#    #+#             */
/*   Updated: 2025/09/01 16:43:44 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	char	**out;
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

void	free_data(t_data *data)
{
	if (data->env)
		free_split(data->env);
	if (data->input)
		free(data->input);
	if (data->token)
		free_tokens(data->token);
}
int	get_data(t_data *data, char **envp)
{
	data->env = copy_env(envp);
	if (!data->env)
		return (1);
	// SHELL SHLVL
		// TODO UPDATE ENV
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	data.i = 0;
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
			free_data(&data);
			exit(0);
		}
		else if (*data.input == 0)
		{
			free(data.input);
		}
		else
		{
			add_history(data.input);
			data.i = 0;
			lex_input(&data);
			if (data.token)
			{
				if (!ft_strcmp("exe", data.token->value))
				{
					ms_heredoc(&data);
					if (ft_executor(&data))
						printf("executor failed in main()\n");
				}
				else
				{
					printf("going into debug mode!\n");
					print_tokens(data.token);
				}
				free_tokens(data.token);
				data.token = NULL;
			}
			free(data.input);
			data.input = NULL;
		}
	}
}
