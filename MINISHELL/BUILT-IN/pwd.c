#include "../LIB/minishell.h"

int	ft_pwd(char **str, int fd)
{
	char *pwd;

	if (!str)
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
	return (0);
}

/*int	main(int ac, char **av)
{
	(void)ac;
	ft_pwd(av, 1);
}*/