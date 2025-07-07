/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:25 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/07 14:23:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

// █
void	print_startup(void)
{
	printf(GREEN
		"               __            __     "
		"       __                  __  __ \n"
		"              / /|          / /|    "
		"      / /|                / /|/ /|\n"
		" _____  ____  ██/  _______  ██/   __"
		"_____ ██ |____    ______  ██ |██ |\n"
		"/    /\\/   /\\ / /|/      /\\ / /| "
		"/      /|██     /\\  /     /\\ ██ |██ |\n"
		"██████ ████ /|██ |███████ /|██ |/███"
		"████/ ███████ /|/██████ /|██ |██ |\n"
		"██ | ██ | ██ |██ |██ |  ██ |██ |██  "
		"   /\\ ██ |  ██ |██    ██ |██ |██ |\n"
		"██ | ██ | ██ |██ |██ |  ██ |██ | ███"
		"███ /|██ |  ██ |████████/ ██ |██ |\n"
		"██ | ██ | ██ |██ |██ |  ██ |██ |/   "
		"  ██/ ██ |  ██ |██/     /|██ |██ |\n"
		"██/  ██/  ██/ ██/ ██/   ██/ ██/ ████"
		"███/  ██/   ██/  ███████/ ██/ ██/ \n"
		RESET
		"\t\t\t\t\t\t by dvavryn & bschwarz\n"
		);
}

int	main(void)
{
	print_startup();

	char	*input;
	
	while (1)
	{
		input = readline("minishell > ");
		if (!strcmp(input, "exit"))
			exit(0);
		printf("Command: >%s< not found\n", input);
		free(input);
	}
}
