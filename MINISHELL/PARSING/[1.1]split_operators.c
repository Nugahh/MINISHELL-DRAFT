#include "../LIB/minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	skip_operator(int i, char c1, char c2)
{
	if (c2 && ((c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<')))
		i += 2;
	else if (c1 == '>' || c1 == '<' || c1 == '|')
		i += 1;
	return (i);
}

t_token	*create_operator(char *str, int start, int end)
{
	t_token	*yo;
	int		x;

	x = 0;
	yo = malloc(sizeof(t_token));
	yo->value = ft_calloc(end + 1, sizeof(char));
	while (x < end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->type = ARG;
	yo->next = NULL;
	return (yo);
}

void	insert_op(t_token **head, char *str, int start, int end)
{
	t_token	*new;
	t_token	*temp;

	new = create_operator(str, start, end);
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	check_insert_op_and_init(t_token **head, char *cmd, int start, int i)
{
	int	x;

	if ((cmd[i] == '>' && cmd[i + 1] != '>')
		|| (cmd[i] == '<' && cmd[i + 1] != '<')
		|| cmd[i] == '|')
		insert_op(head, cmd, start, 1);
	else if ((cmd[i] == '>' && cmd[i + 1] == '>')
		|| (cmd[i] == '<' && cmd[i + 1] == '<'))
		insert_op(head, cmd, start, 2);
	x = skip_operator(i, cmd[i], cmd[i + 1]);
	return (x);
}
