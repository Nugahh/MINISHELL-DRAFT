#include "../LIB/minishell.h"

void	assign_type_and_fd(t_token **token)
{
	if (!(*token))
		return ;
	if ((*token)->value[0] == '<')
		((*token))->type = RIN;
	else if ((*token)->value[1] == '>')
		((*token))->type = DROUT;
	else
		((*token))->type = ROUT;
	if (!((*token))->next)
		return ;
	((*token))->next->type = FD;
}

void	assign_type_and_lim(t_token **token)
{
	(*token)->type = DRIN;
	if (!(*token)->next)
		return ;
	(*token)->next->type = LIM;
}

int	assign_type(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->value[0] == '|')
			temp->type = PIPE;
		if (temp->value[0] == '>' && temp->value[1] != '>')
			assign_type_and_fd(&temp);
		else if (temp->value[1] == '>')
			assign_type_and_fd(&temp);
		if (temp->value[0] == '<' && temp->value[1] != '<')
			assign_type_and_fd(&temp);
		else if (temp->value[1] == '<')
			assign_type_and_lim(&temp);
		temp = temp->next;
	}
	return (ft_check_syntax_error(head));
}
