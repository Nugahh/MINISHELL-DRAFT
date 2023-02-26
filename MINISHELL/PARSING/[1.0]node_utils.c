#include "../LIB/minishell.h"

t_token	*create(char *str, int start, int end)
{
	t_token	*yo;
	int		x;

	x = 0;
	yo = malloc(sizeof(t_token));
	if (!yo)
		return (NULL);
	yo->value = ft_calloc(end + 2, sizeof(char));
	while (x <= end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->value[x] = '\0';
	yo->type = ARG;
	yo->next = NULL;
	return (yo);
}

void	insert(t_token **head, char *str, int start, int end)
{
	t_token	*new;
	t_token	*temp;

	new = create(str, start, end);
	if (!new)
		return (free(new));
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

void	printstr(t_token *head)
{
	t_token	*temp;

	temp = head;
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
