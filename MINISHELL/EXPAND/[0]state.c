#include "../LIB/minishell.h"

void	env_lookup(t_token **head, t_env **env, char *copy)
{
	t_env	*tempv;
	t_token	*temp;

	tempv = *env;
	temp = *head;
	while (tempv)
	{
		printf("tempv->name:%s\n", tempv->name);
		if (ft_strncmp(tempv->name, copy, ft_strlen(tempv->name)) == 0)
		{
			temp->value = ft_strncat(temp->value, temp->value, ft_strlen(temp->value) - ft_strlen(tempv->value) + 1);
			break ;
		}
		tempv = tempv->next;
	}
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
		while (temp->value[i])
		{
			if (state == DEFAULT && temp->value[i] == '$')
			{
				i++;
				copy = ft_substr(temp->value, i, ft_strlen(temp->value) - i);
				printf("copy:%s\n", copy);
				env_lookup(&temp, &tempv, copy);
			}
			i++;
		}
		temp = temp->next;
	}
	free(copy);
}