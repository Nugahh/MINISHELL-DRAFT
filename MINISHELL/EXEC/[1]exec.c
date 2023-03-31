#include "../LIB/minishell.h"

void	ft_init_pipes(t_cmdexec *cmd)
{
	if (cmd->next != NULL)
		if (pipe(cmd->next->fd_pipe) == -1)
			return (perror(" "));
}

void	ft_fork(t_cmdexec **head, t_env **env, char **paths)
{
	pid_t		pid;
	t_cmdexec	*cmd;

	cmd = *head;
	while (cmd)
	{
		if (cmd->next != NULL)
			ft_init_pipes(cmd);
		pid = fork();
		if (pid == -1)
			return (perror("Fork "));
		else if (pid == 0)
			ft_child(head, cmd, paths, env);
		if (cmd->next != NULL)
			close(cmd->next->fd_pipe[1]);
		cmd = cmd->next;
	}
}

int	ft_exec(t_cmdexec **head, t_env **env)
{
	char		**paths;
	int			status;
	t_cmdexec	*cmd;

	cmd = *head;
	paths = get_path_and_split((*env)->envy);
	signal(SIGINT, signal_handler);
	if (cmd && !cmd->next && !ft_is_builtins(cmd))
		return (ft_single(cmd, env, paths), free_paths(paths), 0);
	else if (cmd && !cmd->next && ft_is_builtins(cmd))
		return (free_paths(paths), ft_single_builtin(cmd, env), 0);
	ft_fork(head, env, paths);
	signal(SIGINT, signal_handler);
	while (cmd)
	{
		wait(&status);
		cmd = cmd->next;
	}
	signal(SIGINT, signal_handler);
	return (0);
}
