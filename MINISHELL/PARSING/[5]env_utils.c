#include "../LIB/minishell.h"

char	**ft_env_to_array(t_env **head, int i, int j)
{
	char	**envy;
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envy = ft_calloc(i + 1, sizeof(char *));
	if (!envy)
		return (NULL);
	temp = *head;
	while (temp)
	{
		envy[j] = ft_strjoin(temp->name, "=");
		if (!envy[j])
			return (ft_free_array(envy), NULL);
		envy[j] = ft_strjoin(envy[j], temp->value);
		if (!envy[j])
			return (ft_free_array(envy), NULL);
		j++;
		temp = temp->next;
	}
	return (envy);
}
int	add_env_struct(t_env **head)
{
	t_env	*temp;

	temp = *head;
	temp->envy = ft_env_to_array(head, 0, 0);
	if (!temp->envy)
		return (1);
	return (0);
}
