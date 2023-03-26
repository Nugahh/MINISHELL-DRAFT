#include "../LIB/minishell.h"

int	ft_env(t_env **head, int fd)
{
	t_env	*temp;
	int		i;

	temp = *head;
	i = -1;
	while (temp->envy[++i])
	{
		ft_putstr_fd(temp->envy[i], fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
