#include "../LIB/minishell.h"

int	ft_env(t_env **head, int fd)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		ft_putstr_fd(temp->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(temp->value, fd);
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
	return (0);
}
