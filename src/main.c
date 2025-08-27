/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:32 by bschwarz          #+#    #+#             */
/*   Updated: 2025/08/27 15:54:15 by dvavryn          ###   ########.fr       */
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

int update_env(t_data *data)
{
	ssize_t	i;
	char *tmp1;
	char *tmp2;
	
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp("SHELL=", data->env[i], 6))
		{
			tmp1 = ft_strdup("SHELL=/minishell??");	// TODO: finish path search
			if (!tmp1)
				return (1);
			free(data->env[i]);
			data->env[i] = tmp1;
		}
		else if (!ft_strncmp("SHLVL", data->env[i], 6))
		{
			tmp2 = ft_itoa(ft_atoi(&data->env[i][6]) + 2); // TODO: doesnt work properly
			if (!tmp2)
				return (1);
			tmp1 = ft_strjoin("SHLVL", tmp2);
			free(tmp2);
			free(data->env[i]);
			data->env[i] = tmp1;
		}
	}
	return (0);
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
	if (update_env(data))
	{
		free_data(data);
		return (2);
	}
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
				if (!ft_strcmp("exe", data.token->value))
				{
					printf("going into execution mode!\n");
					ft_executor(data.token->next, data.env);
				}
				else
					print_tokens(data.token);
				free_tokens(data.token);
			}
		}
	}
}
