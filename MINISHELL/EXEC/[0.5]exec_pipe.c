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
		cmd = cmd->next;
	}
}

void	ft_exec_builtins(t_cmdexec **head, t_cmdexec *cmd, t_env **env)
{
	if (*(head) == cmd)
	{
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
		close(cmd->next->fd_pipe[1]);
		close(cmd->next->fd_pipe[0]);
		ft_builtins(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else if (cmd->next == NULL)
	{
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
		close(cmd->fd_pipe[0]);
		close(cmd->fd_pipe[1]);
		ft_builtins(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else if (cmd->next != NULL)
	{
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
		close(cmd->fd_pipe[0]);
		close(cmd->next->fd_pipe[1]);
		ft_builtins(cmd, env);
		exit(EXIT_SUCCESS);
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
	ft_fork(head, env, paths);
	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		wait(&status);
		cmd = cmd->next;
	}
	signal(SIGINT, signal_handler);
	return (0);
}
