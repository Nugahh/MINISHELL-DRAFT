#include "../LIB/minishell.h"

void	ft_free_list(t_token **head)
{
	t_token	*temp;

	if (!(*head))
		return ;
	temp = *head;
	while (temp)
	{
		if (temp->value)
			free(temp->value);
		temp->value = NULL;
		// if (temp->next == NULL)
		// 	return(free(temp));
		temp = temp->next;
	}
}
void	ft_free_env(t_env **head)
{
	t_env	*temp;

	if (!(*head))
		return ;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		temp->value = NULL;
		temp->name = NULL;
		free(temp);
		temp = NULL;
	}
}
