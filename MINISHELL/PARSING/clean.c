#include "../LIB/minishell.h"

void    deletenode(t_token **head, t_token *toDel)
{
    t_token    *temp;
    t_token    *prev;

    temp = *head;
    prev = NULL;
    while (temp && temp != toDel)
    {
        prev = temp;
        temp = temp->next;
    }
    if (toDel->next == NULL)
    {
        free(toDel);
        if (prev == NULL)
            return ;
        prev->next = NULL;
        return ;
    }
    toDel->value = temp->next->value;
    toDel->type = temp->next->type;
    temp->next = temp->next->next;
    free(temp->next);
}

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
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}