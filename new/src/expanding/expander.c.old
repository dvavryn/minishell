/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:05:50 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/03 22:45:52 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int funcheck()
{
	// funcheck...
	return (0);
}

// static char	*ft_charjoin(char const *s1, char const c)
// {
// 	char	*dest;
// 	int		i;

// 	if (!s1 || !c)
// 		return (NULL);
// 	dest = malloc((ft_strlen((char *)s1)
// 				+ 2) * sizeof(char));
// 	if (!dest)
// 		return (NULL);
// 	i = -1;
// 	while (s1[++i] != '\0')
// 		dest[i] = s1[i];
// 	dest[i] = c;
// 	dest[++i] = '\0';
// 	return (dest);
// }

static char	*ft_charjoin(char const *s1, char const c)
{
	char	*dest;
	int		i;

	if (!s1 || !c)
		return (NULL);
	dest = malloc((ft_strlen((char *)s1) + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	dest[i] = c;
	dest[++i] = '\0';
	return (dest);
}

char *ft_getenv(t_data *data, char *tmp)
{
	ssize_t	i;
	char	*search;
	char	*out;

	search = ft_strjoin(tmp, "=");
	if (!search)
		return (NULL);
	i = -1;
	while (data->envp[++i] && ft_strncmp(data->envp[i], search,
		ft_strlen(search)))
		;
	if (data->envp[i])
		out = ft_strdup(&data->envp[i][ft_strlen(search)]);
	else
		out = ft_strdup("");
	free(search);
	if (!out)
		return (NULL);
	return (out);
}

static char	*get_var_name(t_data *data, const char *value, ssize_t *i)
{
	// help me i dont know chinese
	ssize_t	start;
	char	*tmp;
	char	*result;

	if (value[*i] == '?' || value[*i] == '$')
	{
		(*i)++;
		if (value[*i - 1] == '?')
			return (ft_strdup("some stuff"));
		if (value[*i - 1] == '$')
			return (ft_strdup("some other stuff"));
	}
	if (!ft_isalpha(value[*i]) && value[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalpha(value[*i]) || value[*i] == '_')
		(*i)++;
	tmp = ft_substr(value, start, *i - start);
	if (!tmp)
		return (ft_strdup(""));
	result = ft_getenv(data, tmp); //change to our envirement
	free(tmp);
	if (!result)
		return (ft_strdup(""));
	return (ft_strdup(result));
}

// static void	expand_token(t_data *data, t_token *token, char *value)
// {
// 	ssize_t	i;
// 	char	*tmp;
// 	char	*out;
// 	char	*buf;
	
// 	i = -1;
// 	out = ft_strdup("");
// 	if (!out)
// 		ft_exit(data, MAL_ERR, 1);
// 	while (value[++i])
// 	{
// 		buf = out;
// 		if (value[i] == '$')
// 		{
// 			i++;
// 			tmp = get_var_name(value, &i);
// 			if (!tmp)
// 				ft_exit(data, MAL_ERR, 1);
// 			out = ft_strjoin(out, tmp);
// 			free(buf);
// 			free(tmp);
// 			i--;
// 		}
// 		else
// 		{
// 			out = ft_charjoin(out, value[i]);
// 			if (!out)
// 				ft_exit(data, MAL_ERR, 1);
// 			free(buf);
// 		}
// 	}
// 	free(token->value);
// 	token->value = out;
// }

static void	expand_token_value(t_data *data, t_token *token, char *value)
{
	ssize_t	i;
	char	*tmp;
	char	*out;

	i = -1;
	out = ft_strdup("");
	if (!out)
		ft_exit(data, MAL_ERR, MAL_ERR);
	while (value[++(i)])
	{
		if (value[i] == '$')
		{
			i++;
			tmp = out;
			out = ft_strjoin(out, get_var_name(data, value, &i));
			free(tmp);
			if (!out)
				ft_exit(data, MAL_ERR, MAL_ERR);
			i--;
		}
		else
		{
			tmp = out;
			out = ft_charjoin(out, value[i]);
			if (!out)
				ft_exit(data, MAL_ERR, MAL_ERR);
		}
	}
	free(token->value);
	token->value = out;
}

void	expander(t_data *data)
{
	t_token	*cur;

	funcheck();
	cur = data->token;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && cur->quote != 1)
		{
			expand_token_value(data, cur, cur->value);
			if (!cur->value)
				ft_exit(data, MAL_ERR, MAL_ERR);
		}
		cur = cur->next;
	}
}



// int main(void)
// {
// 	t_data data;

// 	ft_bzero(&data, sizeof(t_data));
// 	data.token = ft_calloc(1, sizeof(t_token));
// 	if (!data.token)
// 		return (1);
// 	data.token->value = ft_strdup("$USER");
// 	if (!data.token->value)
// 	{
// 		free(data.token);
// 		return (1);
// 	}
// 	data.token->type = TOKEN_WORD;
// 	data.token->quote = QUOTE_NONE;
// 	expander(&data);
// 	printf("%s\n", data.token->value);
// 	free(data.token->value);
// 	free(data.token);	
// }