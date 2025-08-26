#include "pipex.h"

/*
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile

./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
./pipex heredoc LIMITER cmd cmd1 file

*/
typedef struct	s_pipex
{
	
}	t_pipex;

typedef struct	s_cmd
{
	char		*infile;
	int			in_mode;

	char		**cmd;

	char		*outfile;
	int			out_mode;
	struct s_cmd	*next;
}	t_cmd;

typedef enum 	e_path_type
{
	SEARCH,
	ABSOLUTE,
	RELATIVE,
}	t_path_type;

int	pipex(t_cmd	*cmds, char **envp)
{
	(void)cmds;
	(void)envp;
	return (0);
}
void	free_split(char **split)
{
	ssize_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
char **ft_split_join(char *to_split, char sep, char *to_join)
{
	char	**out;
	char	*tmp;
	char	*tmp2;
	ssize_t	i;

	if (!to_split || !sep)
		return (NULL);
	out = ft_split(to_split, sep);
	if (!out)
		return (NULL);
	if (!to_join)
		return (out);
	i = -1;
	while (out[++i])
	{
		tmp = ft_strjoin(out[i], "/");
		if (!tmp)
			return (free_split(out), NULL);
		tmp2 = ft_strjoin(tmp, to_join);
		free(tmp);
		if (!tmp2)
			return (free_split(out), NULL);
		free(out[i]);
		out[i] = tmp2;
	}
	return (out);
}

char	**get_path(char **envp, char *bin)
{
	char	*tmp;
	char	**out;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		write(2, "ERROR: NO PATH FOUND\n", 21);
		return (NULL);
	}
	tmp = ft_strdup(&envp[i][5]);
	if (!tmp)
	{
		write(2, "ERROR: MALLOC FAILED\n", 21);
		return (NULL);
	}

	out	= ft_split_join(tmp, ':', bin);
	free(tmp);
	if (!out)
	{
		write(2, "ERROR: MALLOC FAILED\n", 21);
		return (NULL);
	}
	return (out);
}

char	*get_access(char **path)
{
	ssize_t	i;
	char	*out;

	i = -1;
	while (path[++i] && access(path[i], F_OK))
		;
	if (!path[i])
	{
		out = NULL;
		write(2, "No such file or directory\n", 26);
	}
	else
		out = ft_strdup(path[i]);
	free_split(path);
	return (out);
}

int	get_path_type(char *bin)
{
	if (bin[0] == '.')
		return (RELATIVE);
	else if (bin[0] == '/')
		return (ABSOLUTE);
	return (SEARCH);
}

char	*shorten_path(char	*str)
{
	ssize_t	i;
	char	*ptr;

	i = -1;
	ptr = ft_strrchr(str, '/');
	while (&str[++i] != ptr || ptr + 1 == 0)
		;
	return (ft_substr(str, 0, i));
}

char	*get_relative_path(char	*bin)
{
	size_t	i;
	char	*out;
	char	*tmp;

	out = getcwd(NULL, 0);
	if (!out)
		return (NULL);
	i = 0;
	while (bin[i] && bin[i] == '.')
	{
		if (ft_strlen(&bin[i]) >= 2 && !ft_strncmp("./", &bin[i], 2))
			i += 2;
		if (ft_strlen(&bin[i]) >= 3 && !ft_strncmp("../", &bin[i], 3))
		{
			i += 3;
			tmp = out;
			out = shorten_path(out);
			free(tmp);
			if (!out)
				return (NULL);
		}
	}
	tmp = out;
	out = ft_strjoin(out, &bin[i - 1]);
	if (!out)
		return (NULL);
	return (out);
}



int main(int argc, char **argv, char **envp)
{
	char	**path;
	char	*executable;
	int		path_type;
	ssize_t	i;

	if (!argv[1] || !argv[1][0])
	{
		write(2, "Missing executable\n", 19);
		return (1);
	}
	path_type = get_path_type(argv[1]);
	if (path_type == RELATIVE)
	{
		executable = get_relative_path(argv[1]);
	}
	else if (path_type == ABSOLUTE)
	{
		executable = ft_strdup(argv[1]);
	}
	else if (path_type == SEARCH)
	{
		if (argv[1])
			path = get_path(envp, argv[1]);
		if (!path)
			return (1);
		executable = get_access(path);
	}
	if (!executable)
		return (1);
	if (access(executable, F_OK))
	{
		write(2, "no such file or directory: ", 28);
		write(2, executable, ft_strlen(executable));
		write(2, "\n", 1);
		return (1);
	}
	else if (access(executable, X_OK))
	{
		write(2, "Permission denied!\n", 20);
		return (1);
	}
	printf("The executable is: %s\n", executable);
	free(executable);
}
