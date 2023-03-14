#include "../LIB/minishell.h"

t_token	*create(char *str, int start, int end)
{
	t_token	*yo;
	int		x;

	x = 0;
	yo = malloc(sizeof(t_token));
	if (!yo)
		return (0);
	yo->value = ft_calloc(end + 2, sizeof(char));
	while (x <= end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->type = ARG;
	yo->next = NULL;
	return (yo);
}

int	insert(t_token **head, char *str, int start, int end)
{
	t_token	*new;
	t_token	*temp;

	new = create(str, start, end);
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

void	printstr(t_token *head)
{
	t_token	*temp;

	temp = head;
	if (head == NULL)
	{
		printf("liste vide\n");
		return ;
	}
	while (temp)
	{
		printf("node:%s+ ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}
int	ft_get_state(char c, int state)
{
	if (state == DEFAULT)
	{
		if (c == '\'')
			state = SINGLE;
		else if (c == '\"')
			state = DOUBLE;
	}
	else if (state == SINGLE)
	{
		if (c == '\'')
			state = DEFAULT;
	}
	else if (state == DOUBLE)
	{
		if (c == '\"')
			state = DEFAULT;
	}
	return (state);
}
