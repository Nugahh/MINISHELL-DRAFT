#include "../LIB/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 130;
}

void	signal_quit(int signal)
{
	(void)signal;
	exit(EXIT_SUCCESS);
}
