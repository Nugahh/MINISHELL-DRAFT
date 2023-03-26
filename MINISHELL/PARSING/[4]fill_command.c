#include "../LIB/minishell.h"

// compter combien de cmd->arg

size_t	token_argcount(t_token **head)
{
	t_token	*temp;
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

t_cmdexec	*create_nodecmd(t_token **head, size_t i, t_cmdexec *new)
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
