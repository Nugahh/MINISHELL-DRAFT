#include "../LIB/minishell.h"

void	deletenode(t_token **head, t_token *toDel)
{
	t_token	*temp;
	t_token	*prev;

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
		temp = temp->next;
	}
}

void	ft_free_env(t_env **env)
{
	t_env	*temp;

	if (!(*env))
		return ;
	temp = *env;
	if (temp->envy)
		ft_free_array(temp->envy);
	while (temp)
	{
		if (temp->name)
		{
			temp->name = NULL;
			free(temp->name);
		}
		if (temp->value)
		{
			temp->value = NULL;
			free(temp->value);
		}
		if (temp->next == NULL)
			return (free(temp));
		temp = temp->next;
	}
	free(temp);
}

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	ft_free_cmdexec(t_cmdexec **head)
{
	t_cmdexec	*temp;

	temp = *head;
	while (temp)
	{
		ft_free_array(temp->arg);
		free(temp->lim);
		temp = temp->next;
	}
}
