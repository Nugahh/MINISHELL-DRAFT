#include "../LIB/minishell.h"

int	ft_is_builtins(t_cmdexec *cmd)
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (1);
	else
		return (0);
}
void	ft_builtins(t_cmdexec **head, t_cmdexec *cmd, t_env **env)
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd->arg, 1);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		ft_cd(cmd->arg);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		ft_pwd(1);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		ft_export(env, cmd->arg);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		ft_unset(env, cmd->arg, 1);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		ft_env(env, 1);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		ft_exit(head, cmd, *env);
}