#include "../LIB/minishell.h"

char	**get_path_and_split(char **envy)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	i = -1;
	while (envy[++i] && !path)
		path = ft_strnstr(envy[i], "PATH=", 5);
	if (!path)
		return (NULL);
	if (path)
	{
		path = ft_substr(path, 5, ft_strlen(path) -5);
		paths = ft_split(path, ':');
		free(path);
	}
	return (paths);
}

char	*check_cmd(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		// free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}
