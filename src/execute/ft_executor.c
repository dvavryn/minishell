#include "minishell.h"

typedef struct s_exe_data
{
	t_token	*tokens;
	char	**envp;
}	t_exe_data;

int	bi_echo(void)
{
	printf("builtin TODO\n");
	return (0);
}

int bi_cd(void)
{
	printf("builtin TODO\n");
	return (0);
}

int	bi_pwd(void)
{
	printf("builtin TODO\n");
	return (0);
}

int	bi_export(void)
{
	printf("builtin TODO\n");
	return (0);
}

int	bi_unset(void)
{
	printf("builtin TODO\n");
	return (0);
}

int	bi_env(char **envp)
{
	ssize_t	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}

int	bi_exit(void)
{
	// in pipes edgecase handeling
	printf("builtin TODO\n");
	return (0);
}

int	check_builtin(char *bin, char **envp)
{
	if (!ft_strcmp(bin, "echo"))
		return (bi_echo(), 1);
	if (!ft_strcmp(bin, "cd"))
		return (bi_cd(), 1);
	if (!ft_strcmp(bin, "pwd"))
		return (bi_pwd(), 1);
	if (!ft_strcmp(bin, "export"))
		return (bi_export()), 1;
	if (!ft_strcmp(bin, "unset"))
		return (bi_unset(), 1);
	if (!ft_strcmp(bin, "env"))
		return (bi_env(envp), 1);
	if (!ft_strcmp(bin, "exit"))
		return (bi_exit(), 1);
	return (0);
}

void	ft_executor(t_token *tokens, char **envp)
{
	t_exe_data	data;

	ft_bzero(&data, sizeof(t_exe_data));
	data.tokens = tokens;
	data.envp = envp;
	while (data.tokens)
	{
		if (check_builtin(data.tokens->value, data.envp))
			;
		else
			printf("%s ", data.tokens->value);
		data.tokens = data.tokens->next;
	}
	(void)tokens;
}