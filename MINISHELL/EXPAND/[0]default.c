#include "../LIB/minishell.h"

/*void	deletenode(t_token *todel)
{
	t_token *temp;

	temp = todel->next;
	todel->value = temp->value;
	todel->type = temp->type;
	todel->next = temp->next;
	free(temp);
}*/

void	deletenode(t_token **head, t_token *todel)
{
	t_token *temp;
	t_token *prev;

	temp = *head;
	prev = NULL;
	while (temp && temp != todel)
	{
		prev = temp;
		temp = temp->next;
	}
	if (todel->next == NULL)
	{
		free(todel);
		prev->next = NULL;
		return ;
	}
	todel->value = temp->next->value;
	todel->type = temp->next->type;
	temp->next = temp->next->next;
	free(temp->next);
}

void	env_lookup(t_token **head, t_env **env, char *copy)
{
	t_env	*tempv;
	t_token	*temp;
	int		len;

	tempv = *env;
	temp = *head;
	while (tempv)
	{
		len = ft_strlen(tempv->value);
		if (ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) == 0)
		{
			if (ft_strlen(tempv->name) != ft_strlen(copy))
				return (deletenode(&temp, temp));
			temp->value = ft_strncat(temp->value, tempv->value, len);
			break;
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

	temp = *head;
	tempv = *env;
	while (temp)
	{
		state = ft_get_state(temp->value[i], state);
		i = 0;
		while (temp->value[i])
		{
			if (state == DEFAULT && temp->value[i] == '$')
			{
				copy = ft_substr(temp->value, i + 1, ft_strlen(temp->value) - i);
				eraser(i, ft_strlen(temp->value), temp->value);
				env_lookup(&temp, &tempv, copy);
			}
			i++;
		}
		temp = temp->next;
	}
	free(copy);
}
