#include "minishell.h"

typedef struct s_exe_data
{
	t_token	*tokens;
}	t_exe_data;

void	ft_executor(t_token *tokens)
{
	t_exe_data	data;

	ft_bzero(&data, sizeof(t_exe_data));
	data.tokens = tokens;
	while (data.tokens)
	{
		printf("%s ", data.tokens->value);
		data.tokens = data.tokens->next;
		printf("\n");
	}

	(void)tokens;
}