#include "../LIB/minishell.h"

void	ft_builtins(t_cmdexec **head, t_env **env, char **envp)
{
	t_cmdexec	*temp;
	t_env		*temp_env;

	temp = *head;
	temp_env = *env;
	if (ft_strcmp(temp->arg[0], "echo") == 0)
		ft_echo(temp->arg, 1);
	else if (ft_strcmp(temp->arg[0], "cd") == 0)
		ft_cd(temp->arg);
	else if (ft_strcmp(temp->arg[0], "pwd") == 0)
		ft_pwd(1);
	else if (ft_strcmp(temp->arg[0], "export") == 0)
		ft_export(temp_env, temp->arg[0], 0);
	else if (ft_strcmp(temp->arg[0], "unset") == 0)
		ft_unset(temp_env, temp->arg, 1);
	else if (ft_strcmp(temp->arg[0], "env") == 0)
		ft_env(temp, 1, envp);
	else if (ft_strcmp(temp->arg[0], "exit") == 0)
		ft_exit(head, env);
}