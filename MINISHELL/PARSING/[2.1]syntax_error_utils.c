#include "../LIB/minishell.h"

void	display_error(t_token **token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd((*token)->value, 2);
	ft_putstr_fd("'\n", 2);
	// g_error = 2;
}