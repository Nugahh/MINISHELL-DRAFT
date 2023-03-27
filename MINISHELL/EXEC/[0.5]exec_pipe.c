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
void	ft_init_pipes(t_cmdexec *cmd)
{
	if (cmd->next != NULL)
		if (pipe(cmd->next->fd_pipe) == -1)
			return (perror(" "));
}
void	ft_fork(t_cmdexec **head, t_env **env, char **paths)
{
	t_cmdexec	*cmd;
	pid_t		pid;
	int			status;

	cmd = *head;
	while (cmd)
	{
		if (cmd->next == NULL)
			return (ft_last(cmd, paths, (*env)->envy));
		ft_init_pipes(cmd);
		pid = fork();
		if (pid == -1)
			return (perror("Fork "));
		else if (pid == 0)
			ft_child(head, cmd, paths, env);
		cmd = cmd->next;
	}
	wait(&status);
}
void	ft_exec_builtins(t_cmdexec **head, t_cmdexec *cmd, t_env **env)
{
	if (*(head) == cmd)
	{
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
		close(cmd->next->fd_pipe[1]);
		close(cmd->next->fd_pipe[0]);
		ft_builtins(cmd, env);
	}
	else if (cmd->next == NULL)
	{
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
		close(cmd->fd_pipe[0]);
		close(cmd->fd_pipe[1]);
		ft_builtins(cmd, env);
	}
	else if (cmd->next != NULL)
	{
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
		close(cmd->fd_pipe[0]);
		close(cmd->next->fd_pipe[1]);
		ft_builtins(cmd, env);
	}
}

int	ft_exec(t_cmdexec **head, t_env **env)
{
	char		**paths;
	int			status;
	t_cmdexec	*cmd;

	cmd = *head;
	paths = get_path_and_split((*env)->envy);
	if (cmd && !cmd->next && !ft_is_builtins(cmd))
		return (ft_single(cmd, env, paths), free_paths(paths), 0);
	else if (cmd && !cmd->next && ft_is_builtins(cmd))
		return (ft_builtins(cmd, env));
	// if (ft_is_builtins(cmd))
	// 	ft_exec_builtins(head, cmd, env);
	// else
	ft_fork(head, env, paths);
	while (cmd)
		wait(&status);
	return (0);
}
