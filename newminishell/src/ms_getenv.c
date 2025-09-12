/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:57:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/12 11:36:15 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char **env, char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (env[i])
	{
		if (!ft_strncmp(s, env[i], len) && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *out;
	
// 	out = ft_strdup(ms_getenv(envp, "PATH"));
// 	if (!out)
// 		return (1);
// 	printf("%s\n", out);
// 	free(out);
// 	return (0);
// }