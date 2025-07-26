t_tokens	*create_ttoken_node(char *token, size_t len)
{
	t_tokens	*out;

	out = malloc(sizeof(t_tokens));
	if (!out)
		return (NULL);
	out->token = ft_strndup(token, len);
	if (!out->token)
	{
		free(out);
		return (NULL);
	}
	out->next = NULL;
	return (out);
}

int	init_ttoken(t_tokens **list, char *token, size_t len)
{
	*list = create_ttoken_node(token, len);
	if (!*list)
	{
		*list = NULL;
		return (1);
	}
	return (0);
}

int	append_ttoken(t_tokens **list, char *token, size_t len)
{
	t_tokens	*ptr;

	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = create_ttoken_node(token, len);
	if  (!ptr->next)
	{
		ptr->next = NULL;
		return (1);
	}
	return (0);
}

int	add_ttoken(t_tokens **list, char **token, size_t len)
{
	int err;

	err = 0;
	if (!*list)
		err = init_ttoken(list, *token, len);
	else
		err = append_ttoken(list, *token, len);
	*token += len;
	if (err)
	{
		printf("minishell: add_ttoken failed\n");
		return (1);
	}
	return (0);
}

t_tokens	*tokenize(const char *input)
{
	t_tokens	*out;
	size_t	i;

	out = NULL;
	while (*input)
	{
		i = 0;
		while (*input && ft_isspace(*input))
			input++;
		if (*input == '<')
		{
			if (*(input + 1) == '<')
				add_ttoken(&out, &input, 2);
			else
				add_ttoken(&out, &input, 1);
		}
		else if (*input == '>')
		{
			if (*(input + 1) == '>')
				add_ttoken(&out, &input, 2);
			else
				add_ttoken(&out, &input, 1);
		}
		else if (*input == '\'')
		{
			while (input[i] && input[i] != '\'')
				i++;
			add_ttoken(&out, &input, i + 1);
		}
		else if (*input == '\"')
		{
			while (input[i] && input[i] != '\"')
				i++;
			add_ttoken(&out, &input, i + 1);
		}
		else if (*input == '|')
		{
			if (*(input + 1) == '|')
				add_ttoken(&out, &input, 2);
			else
				add_ttoken(&out, &input, 1);
		}
		else if (*input == '&' && *(input + 1))
		{
			if (*(input + 1) == '&')
				add_ttoken(&out, &input, 2);
			else
				add_ttoken(&out, &input, 1);
		}
		else if (*input == '(')
			add_ttoken(&out, &input, 1);
		else if (*input == ')')
			add_ttoken(&out, &input, 1);
		else
		{
			while (input[i] && !ft_isspace(input[i]))
				i++;
			add_ttoken(&out, &input, i);
		}
	}
	return (out);
}
