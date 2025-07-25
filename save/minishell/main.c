#include "minishell.h"

typedef struct s_data
{
	char *input;
}	t_data;

int main(void)
{
	t_data data;

	while (1)
	{
		data.input = readline("minishell > ");
		if (!ft_strncmp("exit", data.input, 4))
		{
			free(data.input);
			clear_history();
			exit(0);
		}
		add_history(data.input);		
	}
}