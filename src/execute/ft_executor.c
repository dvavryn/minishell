#include "minishell.h"

typedef struct s_exe_data
{
	t_token	*tokens;
}	t_exe_data;

int ft_strcmp(const char *s1, const char *s2)
{
	return(ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	check_builtin(char *bin)
{
	if (   !ft_strcmp(bin, "echo")
		|| !ft_strcmp(bin, "cd")
		|| !ft_strcmp(bin, "pwd")
		|| !ft_strcmp(bin, "export")
		|| !ft_strcmp(bin, "unset")
		|| !ft_strcmp(bin, "env")
		|| !ft_strcmp(bin, "exit"))
		return (1);
	return (0);
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

	return (0);
}

int	bi_echo(void)
{
	printf("builtin TODO\n");
	return (0);
}

int	bi_exit(void)
{
	// in pipes edgecase handeling
	printf("builtin TODO\n");
	return (0);
}


void	ft_executor(t_token *tokens)
{
	t_exe_data	data;

	ft_bzero(&data, sizeof(t_exe_data));
	data.tokens = tokens;
	while (data.tokens)
	{
		if (check_builtin(data.tokens->value))
		{


		}
		else
			printf("%s ", data.tokens->value);
		data.tokens = data.tokens->next;
		printf("\n");
	}

	(void)tokens;
}