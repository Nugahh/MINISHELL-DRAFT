#include "../LIB/minishell.h"

void	ft_free_list(t_token **head)
{
	t_token	*temp;

	while (head)
	{
		temp = *head;
		*head = (*head)->next;
		if (temp)
			free(temp);
		temp = NULL;
	}
}