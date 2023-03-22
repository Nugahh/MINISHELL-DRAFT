#include "../LIB/minishell.h"

int	rin_file(t_cmdexec *head, t_token *src)
{
	if (src->type == RIN)
	{
		if (head->fd_in != 0)
			close(head->fd_in);
		head->fd_in = open(src->next->value, O_RDONLY);
		if (head->fd_in == -1)
			return (-1);
	}
	else if (src->type == LIM)
	{
		if (head->fd_in != 0)
			close(head->fd_in);
//		head->fd_in = HEREDOC FUNCTION head, src);
		if (head->fd_in == -1)
			return (-1);
	}
	return (0);
}
int	rout_file(t_cmdexec *head, t_token *src)
{
	if (src->type == ROUT)
	{
		if (head->fd_out != 1)
			close(head->fd_out);
		head->fd_out = open(src->next->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (head->fd_out == -1)
			return (-1);
	}
	else if (src->type == DROUT)
	{
		if (head->fd_out != 1)
			close(head->fd_out);
		head->fd_out = open(src->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (head->fd_out == -1)
			return (-1);
	}
	return (0);
}