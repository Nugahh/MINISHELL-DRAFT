#include "../LIB/minishell.h"

void	expand_token(t_token **head, t_env **env, int i, int state)
{
	t_token	*temp;
	t_env	*tempv;
	char	*copy;

	temp = *head;
	tempv = *env;
	while (temp)
	{
		while (temp->value)
		{
			copy = malloc(sizeof(char) * (ft_strlen(temp->value) + 1));
			state = ft_get_state(temp->value[i], state);
			if (state == DEFAULT && temp->value[i] == '$')
			{
				i++;
				while (temp->value[i] != ' ' || temp->value)
					copy = ft_strdup(temp->value[i++]);
				if (ft_strncmp(tempv->name, copy, ft_strlen(copy)) == 0)
					env_lookup(temp, tempv, copy);
			}
		}
		temp = temp->next;
	}
	free(copy);
}

void	env_lookup(t_token **head, t_env **env, char *copy)
{
	t_env	*tempv;
	t_token	*temp;

	tempv = *env;
	temp = *head;
	while (tempv)
	{
		if (ft_strncmp(tempv->name, copy, ft_strlen(copy)) == 0)
		{
			temp->value = copy;
			break ;
		}
		tempv = tempv->next;
	}
}