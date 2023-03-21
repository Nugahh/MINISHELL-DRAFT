#include "../LIB/minishell.h"

void	ft_exit(char **cmd)
{
	ft_putendl_fd("exit\n", 2);
	if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		g_error = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		all_clean();
		exit(g_error);
	}
	else if (cmd[1] && cmd[2])
	{
		g_error = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	else if (cmd[1])
		g_error = ft_atoi(cmd[1]);
	if (g_error > 255)
		g_error = g_error % 256;
	all_clean();
	exit(g_error);
}