#include "../LIB/minishell.h"

int	ft_env(t_env *head, int fd, char **envp)
{
	t_env	*temp;

	temp = head;
	env_parser(envp, &temp, 0, 0);
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
