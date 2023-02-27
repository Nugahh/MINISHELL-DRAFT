#include "../LIB/minishell.h"


void	delete_first_node(t_token **head, t_token *toDel)
{
	t_token *temp;

	temp = *head;
	if (temp == toDel)
	{
		free(temp);
		temp = NULL;
		return ;
	}
}

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
		if (prev->next == NULL)
			return ;
		prev->next = NULL;
		return ;
	}
	toDel->value = temp->next->value;
	toDel->type = temp->next->type;
	temp->next = temp->next->next;
	free(temp->next);
}

void	env_lookup(t_token **head, t_env **env, char *copy, t_token *temp)
{
	t_env	*tempv;
	int		len;

	tempv = *env;
	while (tempv)
	{
		len = ft_strlen(tempv->value);
		if (ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) == 0)
		{
			if (ft_strcmp(tempv->name, copy) != 0)
				return (deletenode(head, temp));
			temp->value = ft_strncat(temp->value, tempv->value, len);
			break ;
		}
		tempv = tempv->next;
	}
}

void	eraser(int i, int len, char *str)
{
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
	str[i] = '\0';
}

void	expand_default(t_token **head, t_env **env, int i, int state)
{
	t_token	*temp;
	t_env	*tempv;
	char	*copy;
	int		len;

	temp = *head;
	tempv = *env;
	while (temp)
	{
		i = 0;
		state = ft_get_state(temp->value[i], state);
		len = ft_strlen(temp->value);
		while (temp->value[i])
		{
			if (state == DEFAULT && temp->value[i] == '$'
				&& ft_get_state(temp->value[i + 1], state) == DEFAULT)
			{
				copy = ft_substr(temp->value, i + 1, len - i);
				printf("%s\n", copy);
				eraser(i, len, temp->value);
				env_lookup(head, &tempv, copy, temp);
				free(copy);
			}
			i++;
		}
		temp = temp->next;
	}
 }
