t_tokens	*tokenize(const char *input)
{
	t_tokens	*out;

	out = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input == '<')
		{
			if (*(input + 1) == '<')
			{
				if (!out)
					init_ttoken(out, input, 2);
				else
					append_ttoken(out, input, 2);
				input += 2;
			}
			else
			{
				if (!out)
					init_ttoken(out, input, 1);
				else
					append_ttoken(out, input, 1);
				input++;
			}
		}
		else if (*input == '>')
		{
			if (*(input + 1) == '>')
			{
				if (!out)
					init_ttoken(out, input, 2);
				else
					append_ttoken(out, input, 2);
				input += 2;
			}
			else
			{
				if (!out)
					init_ttoken(out, input, 1);
				else
					append_ttoken(out, input, 1);
				input++;
			}
		}
		else if (*input == '\'')
		{
			int i = 0;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == 0)
				return (printf("minishell: quotes are not closed\n"), NULL);
			if (!out)
				init_ttoken(out, input, i+1);
			else
				append_ttoken(out, input, i+1);
			input += i + 1;
		}
		else if (*input == '\"')
		{
			int i = 0;
			while (input[i] && input[i] != '\"')
				i++;
			if (!input[i])
				return (printf("minishell: quotes are not closed\n"), NULL);
			if (!out)
				init_ttoken(out, input, i+1);
			else
				append_ttoken(out, input, i+1);
			input += i + 1;
		}
		else if (*input == '|')
		{
			if (*(input + 1) == '|')
			{
				if (!out)
					init_ttoken(out, input, 2);
				else
					append_ttoken(out, input, 2);
				input += 2;
			}
			else
			{
				if (!out)
					init_ttoken(out, input, 1);
				else
					append_ttoken(out, input, 1);
				input++;
			}
		}
		else if (*input == '&' && *(input + 1))
		{
			if (*(input + 1) == '&')
			{
				if (!out)
					init_ttoken(out, input, 2);
				else
					append_ttoken(out, input, 2);
				input += 2;
			}
			else
			{
				if (!out)
					init_ttoken(out, input, 1);
				else
					append_ttoken(out, input, 1);
				input++;
			}
		}
		else if (*input == '(')
		{
			if (!out)
				init_ttoken(out, input, 1);
			else
				append_ttoken(out, input, 1);
		}
		else if (*input == ')')
		{
			if (!out)
				init_ttoken(out, input, 1);
			else
				append_ttoken(out, input, 1);
		}
		else
		{
			int i = 0;
			while (input[i] && !ft_isspace(input[i]))
				i++;
			if (!out)
				init_ttoken(out, input, i);
			else
				append_ttoken(out, input, i);
			input += i;
		}
	}
	return (out);
}
