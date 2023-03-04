#include "../LIB/minishell.h"


/*void	delete_first_node(t_token **head, t_token *toDel)
{
	t_token *temp;

	temp = *head;
	if (temp == toDel)
	{
		free(temp);
		temp = NULL;
		return ;
	}
}*/

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
		else if (tempv->next == NULL && ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) != 0)
		{
			printf("oui\n");
			return (deletenode(head, temp));
		}			
		tempv = tempv->next;
	}
}

char	*ft_strdup_env(int i, char *str)
{
	char *copy;
	int	j;
	int	start;

	start = i;
	j = 0;
	while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] == '_') || ((str[i] >= '0' && str[i] <= '9') && (i != '\0')))
	{
		i++;
		j++;
	}
	copy = malloc(sizeof(char) * j + 1);
	if (!copy)
		return (NULL);
	j = 0;
	while ((str[start] >= 'A' && str[start] <= 'Z') || (str[start] >= 'a' && str[start] <= 'z') 
		|| (str[start] == '_') || ((str[start] >= '0' && str[start] <= '9') && (start != '\0')))
	{
		copy[j] = str[start];
		j++;
		start++;
	}
	copy[j] = '\0';
	return (copy);
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
				copy = ft_strdup_env(i + 1, temp->value);
				printf("%s\n", copy);
				env_lookup(head, &tempv, copy, temp);
				free(copy);
			}
			i++;
		}
		temp = temp->next;
	}
 }
