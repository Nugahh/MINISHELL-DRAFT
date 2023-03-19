#include "../LIB/minishell.h"

// instead of return (1), put a cleaner function

int	open_temp()
{
	int		fd;

	fd = open("/tmp/.heredoc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	return (fd);
}
/*
int	heredoc(t_cmdexec **head)
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
		if(!ft_strncmp(line, ))
	}
}*/