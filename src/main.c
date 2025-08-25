#include "minishell.h"

int	main(void)
{
	t_token	*token;
	char	*input;

	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		else if (input == 0)
		{
			free(input);
		}
		else
		{
			add_history(input);
			token = lex_input(input);
			printf("\n");
			print_tokens(token);
			printf("\n");
			free_tokens(token);
		}
	}
}
