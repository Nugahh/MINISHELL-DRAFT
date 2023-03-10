#include "../LIB/minishell.h"

void	fill_cmd_test(t_cmdexec **head)
{
	t_cmdexec	*temp;
	t_cmdexec	*new;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	new = malloc(sizeof(t_cmdexec));
	new->arg = ft_strdup("ls");
	new->red = NULL;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	temp->next = new;
}

