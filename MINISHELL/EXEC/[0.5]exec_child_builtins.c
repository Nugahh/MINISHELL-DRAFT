#include "../LIB/minishell.h"

void	ft_single_builtin(t_cmdexec *cmd, t_env **env)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	ft_dup_fd(cmd);
	ft_builtins(cmd, env);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	ft_builtin_first(t_cmdexec *cmd, t_env **env)
{
	if (cmd->fd_out > 0 || cmd->fd_in > 0)
	{
		ft_dup_fd(cmd);
		ft_builtins(cmd, env);
	}
	else
	{
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
		close(cmd->next->fd_pipe[1]);
		close(cmd->next->fd_pipe[0]);
		ft_builtins(cmd, env);
	}
}

void	ft_builtin_between_pipes(t_cmdexec *cmd, t_env **env)
{
	if (cmd->fd_out > 0 || cmd->fd_in > 0)
	{
		ft_dup_fd(cmd);
		ft_builtins(cmd, env);
	}
	else
	{
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
		close(cmd->fd_pipe[0]);
		close(cmd->next->fd_pipe[1]);
		ft_builtins(cmd, env);
	}
}

void	ft_builtin_last(t_cmdexec *cmd, t_env **env)
{
	if (cmd->fd_out > 0 || cmd->fd_in > 0)
	{
		ft_dup_fd(cmd);
		ft_builtins(cmd, env);
	}
	else
	{
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
		close(cmd->fd_pipe[0]);
		close(cmd->fd_pipe[1]);
		ft_builtins(cmd, env);
	}
}

void	ft_exec_builtins(t_cmdexec **head, t_cmdexec *cmd, t_env **env)
{
	if (*(head) == cmd)
		ft_builtin_first(cmd, env);
	else if (cmd->next != NULL)
		ft_builtin_between_pipes(cmd, env);
	else if (cmd->next == NULL)
		ft_builtin_last(cmd, env);
	exit(EXIT_SUCCESS);
}
