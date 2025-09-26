/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ben.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:26:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/26 12:19:39 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BEN_H
# define MINISHELL_BEN_H
// test
/* ************************************************************************** */
/*                                    INCLUDES                                */
/* ************************************************************************** */

# include "libft.h"

/* ************************************************************************** */
/*                                  PROTOTYPES                                */
/* ************************************************************************** */

void	lex_input(t_data *data);
void	free_tokens(t_token *token);
void	add_dir_token(t_data *data);
void	add_word_token(t_data *data);
void	add_token_value(t_data *data, int type);
void	add_token(t_data *data, t_token *new);
t_token	*new_token(char *value, int type, int quote);
void	print_tokens(t_token *token);
void	expand_token(t_token *token);

void	ms_heredoc(t_data *data);

#endif