#include "../LIB/minishell.h"

int	heredoc(t_cmdexec **head, t_token **src)
{
	char	*line;
	int		fd[2];
	int		ret;

	pipe(fd);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		ret = get_next_line(0);
		if (ret == -1)
			return (-1);
		if (ft_strcmp(line, (*src)->next->value) == 0)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	if ((*head)->fd_in != 0)
		close((*head)->fd_in);
	(*head)->fd_in = fd[0];
	return (0);
}