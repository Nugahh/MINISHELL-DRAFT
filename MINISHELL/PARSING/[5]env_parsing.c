#include "../LIB/minishell.h"

t_env	*create_env(char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	return (new);
}

int	insert_env(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*temp;

	new = create_env(name, value);
	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	ft_insert_env_and_free(t_env **head, char *name, char *value)
{
	if (insert_env(head, name, value) == 1)
		return (1);
	free(name);
	free(value);
	return (0);
}
int	env_parser(char **envp, t_env **head, int i, int j)
{
	bool	equal;
	char	*name;
	char	*value;

	while (envp[i])
	{
		j = -1;
		equal = false;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=' && equal == false)
			{
				equal = true;
				name = ft_substr(envp[i], 0, j);
				if (!name)
					return (free(name), 1);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				break ;
			}
		}
		if (ft_insert_env_and_free(head, name, value) == 1)
			return (1);
		i++;
	}
	return (add_env_struct(head));
}
