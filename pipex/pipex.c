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

int	pipex(t_cmd	*cmds, char **envp)
{

}

char	**get_path(char **envp)
{
	char	*tmp;
	char	**out;
	size_t	i;

	i = 0;
	while (strncmp(envp[i], "PATH=", 5))
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
	out	= ft_split(tmp, ':');
	free(tmp);
	if (!out)
	{
		write(2, "ERROR: MALLOC FAILED\n", 21);
		return (NULL);
	}
	return (out);
}

void	free_split(char **split)
{
	ssize_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	extract_data(int argc, char **argv, char **envp, )
{

}

int main(int argc, char **argv, char **envp)
{
	(void)argc, (void)argv;

	char **path = get_path(envp);

	ssize_t	i = -1;
	while (path[++i])
		printf("-- %s\n", path[i]);
	free_split(path);
}