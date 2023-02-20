#include "../LIB/minishell.h"

t_token	*create(char *str, int start, int end)
{
	t_token	*yo;
	int		x;

	x = 0;
	yo = malloc(sizeof(t_token));
	yo->value = ft_calloc(end + 1, sizeof(char));
	while (x <= end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->value[x] = '\0';
	yo->type = START;
	yo->next = NULL;
	return (yo);
}

void	insert(t_token **head, char *str, int start, int end)
{
	t_token	*new;
	t_token	*temp;

	new = create(str, start, end);
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