#include "../LIB/minishell.h"

static void	ft_dup_fdin(t_cmdexec *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_in > 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
}

static void	ft_dup_fdout(t_cmdexec *cmd)
{
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_out > 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

void ft_dup_fd(t_cmdexec *cmd)
{
	if (cmd->fd_in > 0)
		ft_dup_fdin(cmd);
	if (cmd->fd_out > 0)
		ft_dup_fdout(cmd);
}


