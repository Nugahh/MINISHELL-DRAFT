#include "../LIB/minishell.h"

void	deletenode(t_token *head)
{
	t_token	*temp;
	t_token	*prev;

	temp = head;
	prev = NULL;

	printf("removing node2\n");

	while (temp)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = temp->next;
	free(temp);
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
			{
				printf("removing node\n");
				return (deletenode(temp));
			}
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
