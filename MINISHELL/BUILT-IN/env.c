#include "../LIB/minishell.h"

int	ft_env(t_env *head, int fd, char **envp)
{
	t_env	*temp;

	temp = head;
	env_parser(envp, &temp, 0);
	while (temp)
	{
		ft_putstr_fd(temp->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(temp->value, fd);
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*env;

	env = NULL;
	ft_env(env, 1, envp);
}