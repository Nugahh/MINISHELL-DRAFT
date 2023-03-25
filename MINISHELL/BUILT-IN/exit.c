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

void	ft_exit(t_cmdexec **head, t_cmdexec *cmd,  t_env *env)
{
	ft_putendl_fd("exit\n", 2);
	if (cmd->arg[1] && ft_strisnum(cmd->arg[1]) == 0)
	{
		g_error = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->arg[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		all_clean(head, env);
		exit(g_error);
	}
	else if (cmd->arg[1] && cmd->arg[2])
	{
		g_error = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	else if (cmd->arg[1])
		g_error = ft_atoi(cmd->arg[1]);
	if (g_error > 255)
		g_error = g_error % 256;
	all_clean(head, env);
	exit(g_error);
}

void	all_clean(t_cmdexec **head, t_env *env)
{
	ft_free_cmdexec(head);
	ft_free_env(&env);
}