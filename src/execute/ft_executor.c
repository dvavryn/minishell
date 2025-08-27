#include "minishell.h"

typedef struct s_exe_data
{
	t_token	*tokens;
	char	**envp;
}	t_exe_data;

int ft_strcmp(const char *s1, const char *s2)
{
	return(ft_strncmp(s1, s2, ft_strlen(s1)));
}



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
		return (bi_echo());
	if (!ft_strcmp(bin, "cd"))
		return (bi_cd());
	if (!ft_strcmp(bin, "pwd"))
		return (bi_pwd());
	if (!ft_strcmp(bin, "export"))
		return (bi_export());
	if (!ft_strcmp(bin, "unset"))
		return (bi_unset());
	if (!ft_strcmp(bin, "env"))
		return (bi_env(envp));
	if (!ft_strcmp(bin, "exit"))
		return (bi_exit());
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
		printf("\n");
	}

	(void)tokens;
}