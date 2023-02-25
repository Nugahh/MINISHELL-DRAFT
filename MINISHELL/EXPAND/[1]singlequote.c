#include "../LIB/minishell.h"

void	copy_single(t_token *temp, int i, char *copy)
{
	while (copy[i] != '\'')
	{
		temp->value[i] = copy[i];
		i++;
	}
	temp->value[i] = '\0';
}

void	expand_single(t_token **head, int s, int i, char *copy)
{
	t_token	*t;

	t = *head;
	while (t)
	{
		i = -1;
		while (t->value[++i])
		{
			s = ft_get_state(t->value[i], s);
			if (s == SINGLE && t->value[i] == '\'' && t->value[i + 1] != '\'')
			{
				copy = ft_substr(t->value, i + 1, ft_strlen(t->value));
				if (!copy)
					return ;
				ft_bzero(t->value, ft_strlen(t->value));
				i = 0;
				copy_single(t, i, copy);
				free(copy);
			}
			else if (s == SINGLE && t->value[i] == '\''
				&& t->value[i + 1] == '\'')
				deletenode(head, t);
		}
		t = t->next;
	}
}
