#include "../LIB/minishell.h"

void	expand_single(t_token **head, int state)
{
	t_token	*temp;
	int		i;
	char	*copy;

	temp = *head;
	while (temp)
	{
		i = 0;
		while (temp->value[i])
		{
			state = ft_get_state(temp->value[i], state);
			if (state == SINGLE && temp->value[i] == '\'' && temp->value[i + 1] != '\'')
			{
				copy = ft_substr(temp->value, i + 1, ft_strlen(temp->value));
				if (!copy)
					return ;
				ft_bzero(temp->value, ft_strlen(temp->value));
				i = 0;
				while (copy[i] != '\'')
				{
					temp->value[i] = copy[i];
					i++;
				}
				temp->value[i] = '\0';
				free(copy);
			}
			else if (state == SINGLE && temp->value[i] == '\'' && temp->value[i + 1] == '\'')
				deletenode(head, temp);
			i++;
		}
		temp = temp->next;
	}
}