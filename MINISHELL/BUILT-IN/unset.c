#include "../LIB/minishell.h"

static void	free_unset(t_env **env)
{
	t_env	*temp;

	temp = *env;
	free(temp->name);
	free(temp->value);
	free(temp);
}

int	ft_unset(t_env **env, char **command, int i)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	while (command[i])
	{
		while (temp)
		{
			if (ft_strncmp(temp->name, command[i], ft_strlen(command[i])) == 0)
			{
				if (prev == NULL)
					*env = temp->next;
				else
					prev->next = temp->next;
				free_unset(&temp);
				break ;
			}
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	return (add_env_struct(env), 0);
}
