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

void	copy_double(t_token *temp, int i, char *copy)
{
	while (copy[i] != '\"' )
	{
		temp->value[i] = copy[i];
		i++;
	}
	temp->value[i] = '\0';
}

/*int	modulo_quote(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count += 1;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}*/

void	ft_check_state_and_expand(t_token **head, t_env **env)
{
	t_token *temp;
	t_env	*tempv;
	int		state;
	int		i;

	temp = *head;
	tempv = *env;
	state = 0;
	while (temp)
	{
		if (temp->type == ARG || temp->type == FD)
		{	
			i = 0;
			while (temp->value[i])
			{
				state = ft_get_state(temp->value[i], state);
				if (state == SINGLE)
					expand_single(head, DEFAULT, 0, NULL);
				else if (state == DOUBLE)
					expand_double(head, &tempv, 0, DEFAULT);
				else if (state == DEFAULT)
					expand_default(head, &tempv, 0, DEFAULT);
				i++;
			}
		}
		temp = temp->next;
	}
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
			printf("t->value[i] = %c\n", t->value[i]);
			printf("t->value[i + 1] = %c\n", t->value[i + 1]);
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
				&& t->value[i + 1] == '\'' && t->value[i + 2] == '\0')
				deletenode(head, t);
		}
		t = t->next;
	}
}

void	expand_in_double(t_token **head, t_env **env, int i, int state)
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
		printf("temp->value[i] = %c\n", temp->value[i]);
		while (temp->value[i])
		{
			if (temp->value[i] == '$')
			{

				copy = ft_substr(temp->value, i + 1, len - i - 2);
				// printf("TEST %s\n", copy);
				eraser(i, len, temp->value);
				env_lookup(head, &tempv, copy, temp);
				free(copy);
			}
			i++;
		}
		temp = temp->next;
	}
}

void	expand_double(t_token **head, t_env **env, int s, int i)
{
	t_token	*t;
	t_env	*tempv;
	char	*copy;

	t = *head;
	tempv = *env;
	while (t)
	{
		i = -1;
		while (t->value[++i])
		{
			s = ft_get_state(t->value[i], s);
//			printf("t->value[i] = %c\n", t->value[i]);
//			printf("t->value[i + 1] = %c\n", t->value[i + 1]);
//			printf("s = %d\n", s);
			if (s == DOUBLE && t->value[i] == '\"' && t->value[i + 1] != '\"')
			{
				copy = ft_substr(t->value, i + 1, ft_strlen(t->value));
				if (!copy)
					return ;
				ft_bzero(t->value, ft_strlen(t->value));
				i = 0;
				copy_double(t, i, copy);
				printf("copy = %s\n", copy);
				free(copy);
				expand_in_double(&t, env, 0, DEFAULT);
			}
			else if (s == DOUBLE && t->value[i] == '\"'
				&& t->value[i + 1] == '\"' && t->value[i + 2] == '\0')
				deletenode(head, t);
		}
		t = t->next;
	}
}
