#include "minishell.h"

int	main(void)
{
	char *input;

	while (1)
	{
		input=readline("minishell > ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		else if (input = 0 )
		{
			free(input);
		}
		else
		{
			add_history(input);
		}
	}
}