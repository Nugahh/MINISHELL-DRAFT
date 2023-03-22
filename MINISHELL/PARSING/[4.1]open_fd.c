#include "../LIB/minishell.h"

int	rin_file(t_cmdexec **head, t_token **src)
{
	if ((*src)->type == RIN)
	{
		if ((*head)->fd_in != 0)
			close((*head)->fd_in);
		(*head)->fd_in = open((*src)->next->value, O_RDONLY);
		if ((*head)->fd_in == -1)
			return (-1);
	}
	else if ((*src)->type == DRIN)
	{
		if ((*head)->fd_in != 0)
			close((*head)->fd_in);
		(*head)->lim = ft_strdup((*src)->next->value);
		(*head)->fd_in = open_temp();
		if ((*head)->fd_in == -1)
			return (-1);
	}
	return (0);
}
int	rout_file(t_cmdexec **head, t_token **src)
{
	if ((*src)->type == ROUT)
	{
		if ((*head)->fd_out != 1)
			close((*head)->fd_out);
		(*head)->fd_out = open((*src)->next->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*head)->fd_out == -1)
			return (-1);
	}
	else if ((*src)->type == DROUT)
	{
		if ((*head)->fd_out != 1)
			close((*head)->fd_out);
		(*head)->fd_out = open((*src)->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*head)->fd_out == -1)
			return (-1);
	}
	return (0);
}

void	fill_fd(t_cmdexec **head)
{
	t_cmdexec *temp;

	temp = *head;
	if (temp && temp->next == NULL)
		return ;
	else if (temp && temp->next)
	{
		temp->fd_out = 1;
		temp = temp->next;
	}
	while (temp)
	{
		if (temp->next == NULL)
			temp->fd_in = 1;
		else
		{
			temp->fd_in = 1;
			temp->fd_out = 1;
		}
		temp = temp->next;
	}
}