#include "../LIB/minishell.h"

int	ft_exit(char **cmd)
{
	ft_putendl_fd("exit", 2);
	if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		g_error = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (cmd[1] && cmd[2])
	{
		g_error = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (cmd[1])
		g_error = ft_atoi(cmd[1]);
	return (g_error);
}