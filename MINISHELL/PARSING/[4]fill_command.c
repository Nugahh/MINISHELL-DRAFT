#include "../LIB/minishell.h"

// compter combien de cmd->arg

size_t	token_argcount(t_token **head)
{
	t_token *temp;
	size_t	count;

	temp = *head;
	count = 0;
	while (temp)
	{
		if (temp->type == ARG)
			count++;
		else if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (count);
}

t_cmdexec *create_nodecmd(t_token **head, size_t i, t_cmdexec *new)
{
	t_token		*temp;

	temp = *head;
	new = malloc(sizeof(t_cmdexec));
	new->arg = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (temp)
	{
		new->fd_in = 0;
		new->fd_out = 0;
		if (temp->type == ARG)
		{
			new->arg[i] = ft_strdup(temp->value);
			i++;
		}
		else if (temp->type != ARG && temp->type != PIPE)
			fill_redir(new, temp);
		else if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	new->next = NULL;
	return (new);
}
void	fill_redir(t_cmdexec *tofill, t_token *src)
{
	tofill->fd_out = 1;
	if (src->type == RIN || LIM)
		rin_file(tofill, src);
	else if (src->type == ROUT || DROUT)
		rout_file(tofill, src);
}

int	insert_nodecmd(t_cmdexec **head, t_token **token)
{
	t_cmdexec	*new;
	t_cmdexec	*temp;

	new = create_nodecmd(token, token_argcount(token), NULL);
	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

void	cmd_final(t_cmdexec **head, t_token **token)
{
	insert_nodecmd(head, token);
	while (*token)
	{
		if ((*token)->type == PIPE)
		{
			*token = (*token)->next;
			insert_nodecmd(head, token);
		}
		else if ((*token)->next == NULL)
			return (ft_free_list(token));
		(*token) = (*token)->next;
	}
}
void	printcmdexec(t_cmdexec *head)
{
	t_cmdexec	*temp;
	int			i;	

	temp = head;
	if (head == NULL)
	{
		printf("liste vide\n");
		return ;
	}
	while (temp)
	{
		printf("command: ");
		i = 0;
		while(temp->arg[i])
		{
			printf("arg = %s | ", temp->arg[i]);
			i++;
		}
		printf("red = %s | ", temp->red);
		printf("fd_in = %d | ", temp->fd_in);
		printf("fd_out = %d\n", temp->fd_out);
		temp = temp->next;
	}
}

void	ft_free_cmdexec(t_cmdexec **head)
{
	t_cmdexec	*temp;
	int			i;

	i = 0;
	temp = *head;
	while (temp)
	{
		while (temp->arg[i])
		{
			free(temp->arg[i]);
			i++;
		}
		free(temp->arg);
		free(temp->red);
		temp = temp->next;
	}
}
