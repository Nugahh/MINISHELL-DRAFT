#include "../LIB/minishell.h"


void	ft_single(t_cmdexec *cmd, t_env **env, char **paths)
{
	pid_t	pid;
	int		status;
	char	*path_cmd;

	pid = fork();
	if (pid == -1)
		return (perror("Fork "));
	else if (pid == 0)
	{
		path_cmd = check_cmd(cmd->arg[0], paths);
		if (path_cmd == NULL)
			return (perror("Command not found: "));
		if (execve(path_cmd, cmd->arg, (*env)->envy) == -1)
			return (perror("Execve "));
	}
	wait(&status);
}

void	ft_first(t_cmdexec *cmd, char **paths, char **env)
{
	char	*path_cmd;

	dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
	close(cmd->next->fd_pipe[1]);
	close(cmd->next->fd_pipe[0]);
	path_cmd = check_cmd(cmd->arg[0], paths);
	if (path_cmd == NULL)
		return (perror("Command not found: "));
	if (execve(path_cmd, cmd->arg, env) == -1)
		return (perror("Execve "));
}

void	ft_last(t_cmdexec *cmd, char **paths, char **env)
{
	char	*path_cmd;

	dup2(cmd->fd_pipe[0], STDIN_FILENO);
	close(cmd->fd_pipe[0]);
	close(cmd->fd_pipe[1]);
	path_cmd = check_cmd(cmd->arg[0], paths);
	if (path_cmd == NULL)
		return (perror("Command not found: "));
	if (execve(path_cmd, cmd->arg, env) == -1)
		return (perror("Execve "));
}

void	ft_between_pipes(t_cmdexec *cmd, char **paths, char **env)
{
	char	*path_cmd;

	dup2(cmd->fd_pipe[0], STDIN_FILENO);
	dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
	close(cmd->fd_pipe[0]);
	close(cmd->next->fd_pipe[1]);
	path_cmd = check_cmd(cmd->arg[0], paths);
	if (path_cmd == NULL)
		return (perror("Command not found: "));
	if (execve(path_cmd, cmd->arg, env) == -1)
		return (perror("Execve "));
}

void	ft_child(t_cmdexec **head, t_cmdexec *cmd, char **paths, t_env **env)
{
	if (ft_is_builtins(cmd))
		ft_exec_builtins(head, cmd, env);
	else
	{
		if ((*head) == cmd)
			ft_first(cmd, paths, (*env)->envy);
		if (cmd->next == NULL)
			ft_last(cmd, paths, (*env)->envy);
		else if (cmd->next != NULL)
			ft_between_pipes(cmd, paths, (*env)->envy);
	}
}
