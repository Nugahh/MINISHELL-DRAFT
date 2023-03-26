#include "../LIB/minishell.h"

// int	ft_pipe(t_cmdexec **head, t_env **env, char **paths)
// {
// 	int		status;
// 	t_cmdexec	*cmd;

// 	cmd = *head;
// 	if (cmd && cmd->next == NULL)
// 		return (ft_single(head, paths), free_paths(paths), 0);
// 	while (cmd)
// 	{
// 		if (cmd->next == NULL)
// 			ft_last(head, paths);
// 		else
// 			ft_child(head, paths);
// 		wait(&status);
// 		cmd = cmd->next;
// 	}
// 	free_paths(paths);
// 	return (0);
// }

void	ft_fork(t_cmdexec **head, t_env **env, char **paths)
{
	pid_t		pid;
	t_cmdexec	*cmd;
	int			status;
	int			fd_pipe[2];

	(void)env;
	cmd = *head;
	while (cmd)
	{
		if (cmd->next == NULL)
			return (ft_last(cmd, paths, fd_pipe, env));
		if (pipe(fd_pipe) == -1)
			return (perror(" "));
		pid = fork();
		if (pid == -1)
			return (perror("Fork "));
		else if (pid == 0)
			ft_child(cmd, paths, fd_pipe, env);
		cmd = cmd->next;
	}
	wait(&status);
}

int	ft_exec(t_cmdexec **head, t_env **env)
{
	char		**paths;
//	pid_t		pid;
	t_cmdexec	*cmd;

	cmd = *head;
	paths = get_path_and_split((*env)->envy);
//	if (cmd && !cmd->next)
//		return (ft_single(cmd, env, paths), free_paths(paths), 0);
//	pid = fork();
//	if (pid == -1)
//		return (perror("Fork "), 1);
//	else if (pid == 0)
//		ft_first(cmd, paths, env);
	while (cmd)
	{
		if (ft_is_builtins(cmd))
			ft_builtins(cmd, env);
		else
			ft_fork(head, env, paths);
		cmd = cmd->next;
	}
	return (0);
}