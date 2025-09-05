/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:41:10 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/05 13:29:41 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "minishell.h"

void	add_token(t_data *data, t_token *to_add);
t_token	*new_token(char	*value, int type, int qute);

int		add_word_token(t_data *data);
void	add_pipe_token(t_data *data);
void	add_redir_token(t_data *data);
void	add_token_value(t_data *data, int type);

void	cleanup_token(t_data *data);

#endif
