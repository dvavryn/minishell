/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:41:28 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 17:41:38 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_type(t_token *ptr)
{
	if (ptr->type == TOKEN_WORD)
		printf("TYPE:\tWORD\n");
	else if (ptr->type == TOKEN_PIPE)
		printf("TYPE:\tPIPE\n");
	else if (ptr->type == TOKEN_REDIR_IN)
		printf("TYPE:\tRED_IN\n");
	else if (ptr->type == TOKEN_REDIR_OUT)
		printf("TYPE:\tRED_OUT\n");
	else if (ptr->type == TOKEN_HEREDOC)
		printf("TYPE:\tHEREDOC\n");
	else if (ptr->type == TOKEN_APPEND_OUT)
		printf("TYPE:\tAPPEND_OUT\n");
}

static void	print_quote(t_token *ptr)
{
	if (ptr->quote == QUOTE_NONE)
		printf("QUOTE:\tNONE\n");
	else if (ptr->quote == QUOTE_SINGLE)
		printf("QUOTE:\tSINGLE\n");
	else if (ptr->quote == QUOTE_DOUBLE)
		printf("QUOTE:\tDOUBLE\n");
	else if (ptr->quote == QUOTE_HD)
		printf("QUOTE:\tHD\n");
}

void	print_token(t_token *token)
{
	t_token	*ptr;

	if (!token)
		return ;
	ptr = token;
	while (ptr)
	{
		printf("\n= = = = = = = = = =\n");
		print_type(ptr);
		printf("VALUE:\t%s\n", ptr->value);
		print_quote(ptr);
		printf("= = = = = = = = = =\n\n");
		ptr = ptr->next;
	}
}
