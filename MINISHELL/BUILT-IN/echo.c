#include "../LIB/minishell.h"

static int	check_flag(char **str)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 0;
	i = 0;
	while (str[i] && ft_strlen(str[i]) >= 2)
	{
		if (str[i][j] == '-' && str[i][j + 1] == 'n')
		{
			j++;
			while (str[i][j] == 'n')
				j++;
			if (j == ft_strlen(str[i]))
				count++;
		}
		else
			return (count);
		i++;
		j = 0;
	}
	return (count);
}

int	ft_echo(char **str, int fd)
{
	int	i;
	int	n;

	str++;
	n = 0;
	i = check_flag(str);
	if (i > 0)
		n++;
	while (str[i])
	{
		if (str[i][0] == '$' && str[i][1] == '?')
			return (ft_putstr_fd(ft_itoa(g_error), 1), write(1, "\n", 1), 0);
		ft_putstr_fd(str[i], fd);
		if (str[i + 1] && str[i][0] != '\0')
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}

/*int main (int ac, char **av)
{
	(void)ac;
	ft_echo(av);
}*/