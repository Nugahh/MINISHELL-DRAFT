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
	new = ft_calloc(1, sizeof(t_cmdexec));
	new->arg = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	new->fd_in = 0;
	new->fd_out = 0;
	while (temp)
	{
		if (temp->type == ARG)
			new->arg[++i] = ft_strdup(temp->value);
		else if (temp->type == DRIN)
		{
			fill_redir(new, temp);
			break ;
		}
		else if (temp->type == PIPE)
			break ;
		else if (temp->type >= 0 && temp->type <= 6)
			fill_redir(new, temp);
		printf("new->fd_in: %d | new->fd_out: %d\n", new->fd_in, new->fd_out);
		temp = temp->next;
	}
	new->next = NULL;
	return (new);
}

void	fill_redir(t_cmdexec *tofill, t_token *src)
{
	tofill->lim = NULL;
	if (src->type == RIN || src->type == DRIN)
		rin_file(tofill, src);
	else if (src->type == ROUT || src->type == DROUT)
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
		if (temp->arg[0])
		{	
			while(temp->arg[i])
			{
				printf("arg = %s | ", temp->arg[i]);
				i++;
			}
		}
		printf("lim = %s | ", temp->lim);
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
		if (temp->arg[i])
		{
			while (temp->arg[i])
			{
				free(temp->arg[i]);
				i++;
			}
		}
		free(temp->arg);
		free(temp->lim);
		temp = temp->next;
	}
}
