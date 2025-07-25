#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int sig;

__sighandler_t	handle_sigint(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (0);
}

__sighandler_t handle_sigquit(void)
{
	return (0);
}

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell > ");

		// ctrl-d
		if (!input)
		{
			clear_history();
			printf("exit\n");
			exit(0);
		}
		else if (*input)
		{
			add_history(input);
		}
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, &handle_sigquit);
		free(input);
	}

}