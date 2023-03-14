#include "../LIB/minishell.h"

int	ft_cd(char **command)
{
	char	*path;
	char	*pwd;

	if (command[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
			return (free(path), 1);
	}
	else if (ft_strncmp(command[1], "-", 1) == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			return (free(path), 1);
	}
	else
		path = command[1];
	if (chdir(path) == -1)
		printf("cd: %s: No such file or directory", path);
	return (free(path), 0);
}
