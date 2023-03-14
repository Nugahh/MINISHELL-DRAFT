#include "../LIB/minishell.h"

// compter combien de cmd->arg

size_t	token_argcount(t_token **head)
{
	t_token *temp;
	size_t	i;

	temp = *head;
	i = 0;
	while (temp)
	{
		if (temp->type == ARG)
			i++;
		temp = temp->next;
	}
	return (i);
}

t_cmdexec *create_command(t_token **head)
{
	t_token	*temp;
	t_cmdexec	*new;
	size_t	i;

	temp = *head;
	i = token_argcount(&temp);
	new = malloc(sizeof(t_cmdexec));
	new->arg = malloc(sizeof(char *) * (i + 1));
	while (temp)
	{
		if (temp->type == ARG)
			new->arg[i] = ft_strdup(temp->value);
		else if (temp->type == DRIN)
			new->fd_in = ft_atoi(temp->value);
		else if (temp->type == DROUT)
			new->fd_out = ft_atoi(temp->value);
		else if (temp->type == RIN || temp->type == ROUT)
			new->red = ft_strdup(temp->value);
		i++;
		temp = temp->next;
	}
	new->next = NULL;
	return (new);
}