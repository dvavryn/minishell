char *expand_home(char *str)
{
	char	*user;
	char	*out;
	char	*tmp;

	user = getenv("USER");
	tmp = ft_strjoin("/home/", user);
	if (!tmp)
		return (NULL);
	out = ft_strjoin(tmp, str+1);
	if (!out)
		return (NULL);
	free(tmp);
	return (out);
}