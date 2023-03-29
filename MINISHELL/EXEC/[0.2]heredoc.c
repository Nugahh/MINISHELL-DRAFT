#include "../LIB/minishell.h"

int	open_temp(void)
{
	int		fd;

	fd = open("/tmp/.heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc"), 1);
	return (fd);
}

void	signal_heredoc(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_error = 130;
	}
}

int	heredoc(t_cmdexec *cmd)
{
	int		temp;
	int		fd_in;
	char	*line;

	temp = open_temp();
	fd_in = dup(STDIN_FILENO);
	ft_putstr_fd("> ", 1);
	line = get_next_line(fd_in);
	while (line)
	{
		if (!ft_strncmp(line, cmd->lim, ft_strlen(cmd->lim))
			&& ft_strlen(cmd->lim) + 1 == ft_strlen(line))
			break ;
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, temp);
		free(line);
		line = get_next_line(fd_in);
	}
	if (line)
		free(line);
	close (fd_in);
	close (temp);
	return (0);
}
