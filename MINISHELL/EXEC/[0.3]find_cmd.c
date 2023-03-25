#include "../LIB/minishell.h"

char	**get_path_and_split(t_env **env)
{
	char	*path;
	char	**paths;
	t_env	*temp_env;

	path = NULL;
	temp_env = *env;
	while (temp_env && !path)
	{
		if (ft_strncmp(temp_env->name, "PATH", 4) == 0)
			path = ft_strdup(temp_env->value);
		temp_env = temp_env->next;
	}
	paths = ft_split(path, ':');
	if (path)
		free(path);
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
