#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define SHELLNAME "minishell > "

volatile int	g_signal;

void handle_sigint(int sig)
{
	g_signal = sig;
	rl_on_new_line();
	rl_replace_line(SHELLNAME, 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
}

int main(void)
{
	struct	sigaction s_int;
	struct	sigaction s_quit;

	s_int.sa_handler = &handle_sigint;
	sigaction(SIGINT, &s_int, NULL);
	
	s_quit.sa_handler = &handle_sigquit;
	sigaction(SIGQUIT, &s_quit, NULL);
	
	char *input;
	while (1)
	{
		input = readline(SHELLNAME);
		if (g_signal == SIGINT)
			input = readline(SHELLNAME);
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
		free(input);
	}
}