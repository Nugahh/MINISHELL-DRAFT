#include "../LIB/minishell.h"

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// void	ft_exit(t_cmdexec *cmd, t_env *env)

// {
// 	ft_putendl_fd("exit", 1);
// 	if (cmd->arg[1] && ft_strisnum(cmd->arg[1]) == 0)
// 	{
// 		g_error.status = 255;
// 		ft_putstr_fd("minishell: exit: ", 2);
// 		ft_putstr_fd(cmd->arg[1], 2);
// 		ft_putendl_fd(": numeric argument required", 2);
// 		all_clean(cmd, env);
// 		exit(g_error.status);
// 	}
// 	else if (cmd->arg[1] && cmd->arg[2])
// 	{
// 		g_error.status = 1;
// 		ft_putendl_fd("minishell: exit: too many arguments", 2);
// 		return ;
// 	}
// 	else if (cmd->arg[1])
// 		g_error.status = ft_atoi(cmd->arg[1]);
// 	if (g_error.status > 255)
// 		g_error.status = g_error.status % 256;
// 	all_clean(cmd, env);
// 	exit(g_error.status);
// }

void	all_clean(t_cmdexec *head, t_env *env)
{
	ft_free_cmdexec(&head);
	ft_free_env(&env);
}
