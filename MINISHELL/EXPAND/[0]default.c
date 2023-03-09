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

int	env_lookup(t_env **env, char *copy)
{
	t_env	*tempv;

	tempv = *env;
	while (tempv)
	{
		if (ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) == 0)
		{
			if (ft_strcmp(tempv->name, copy) != 0)
				return (1);
			return (2);
		}
		else if (tempv->next == NULL && ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) != 0)
			return (1);
		tempv = tempv->next;
	}
	return (0);
}

char	*new_envname(t_env **env, char *copy)
{
	t_env	*tempv;

	tempv = *env;
	while (tempv)
	{
		if (ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) == 0)
		{
			ft_bzero((char *)copy, ft_strlen(copy));
			copy = ft_strdup(tempv->value);
			if (!copy)
				return (NULL);
		}
		tempv = tempv->next;
	}
	return (copy);
}

void	node_changer(t_token **head, t_env **env, char *copy, t_token *temp)
{
	int i;
	int	j;
	int len;
	char 	*first_copy;
	char	*final_copy;
	int	envlookup;

	j = 0;
	i = 0;
	first_copy = NULL;
	final_copy = NULL;
	len = ft_strlen(copy) +1;
	envlookup = env_lookup(env, copy);
	if (envlookup == 1)
	{
		if(temp->value[0] == '$')
			return (deletenode(head, temp));
		while(temp->value[i] != '$')
			i++;
		first_copy = ft_substr(temp->value, 0, i + 1);
		if (!first_copy)
			return ;
		temp->value = NULL;
		temp->value = ft_strdup(first_copy);
		return (free(first_copy));
	}
	else if (envlookup == 2)
	{
		copy = new_envname(env, copy);
		if (temp->value[0] == '$' && ft_strlen(temp->value) == len)
		{
			ft_bzero(((char *)temp->value), ft_strlen(temp->value));
			temp->value = ft_strdup(copy);
			if (!temp->value)
				return;
			return ;
		}
		while (temp->value[i] != '$')
			i++;
		if (i != 0)
		{
			first_copy = ft_substr(temp->value, 0, i);
			len = ft_strlen(copy) + ft_strlen(first_copy);
			if (!first_copy)
				return ;
		}
		while (i < len)
			i++;
		j = i;
		while ((!((temp->value[i] >= 'A' && temp->value[i] <= 'Z') && (temp->value[i] >= 'a' && temp->value[i] <= 'z') 
		&& (temp->value[i] == '_') && (temp->value[i] >= '0' && temp->value[i] <= '9'))) && (temp->value[i + 1] != '\0'))
			i++;
		if (i != (ft_strlen(temp->value)))
		{
			final_copy = ft_substr(temp->value, j, i - j + 1);
			if (!final_copy)
				return ;
		}
		temp->value = NULL;
		if (first_copy && !final_copy)
		{
			temp->value = ft_strncat(first_copy, copy, ft_strlen(copy) + ft_strlen(first_copy));
			return ;
		}
		else if (!first_copy && final_copy)
		{
			temp->value = ft_strncat(copy, final_copy, len + ft_strlen(final_copy));
			return (free(final_copy));
		}
		else if (first_copy && final_copy)
		{
			temp->value = ft_strncat(first_copy, copy, len + ft_strlen(first_copy));
			temp->value = ft_strncat(temp->value, final_copy, ft_strlen(temp->value) + ft_strlen(final_copy));
			return ;
		}
		else
			temp->value = ft_strdup(copy);
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

void	expand(t_token **head, t_env **env, int i)
{
	t_token	*temp;
	t_env	*tempv;
	char	*copy;

	temp = *head;
	tempv = *env;
	while (temp)
	{
		i = 0;
		while (temp->value[i])
		{
			if (temp->value[i] == '$')
			{
				copy = ft_strdup_env(i + 1, temp->value);
				node_changer(head, &tempv, copy, temp);
				free(copy);
				return ;;
			}
			if (temp->next == NULL && temp->value[i + 1] == '\0')
				break;
			i++;
		}
		temp = temp->next;
	}
 }
