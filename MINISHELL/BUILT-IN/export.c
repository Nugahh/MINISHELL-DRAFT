#include "../LIB/minishell.h"

int		check_varexp(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '=' || check_equal(str) == 0)
		return (export_error(str), 1);
	while (str[i])
	{
		if (check_symbolerror(str[i]))
			return (export_error(str), 1);
		i++;
	}
	return (0);
}

void	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	update_env(t_env *tempv, char *value)
{
		if (head->value)
			free(head->value);
		head->value = ft_strdup(value);
		if (!head->value)
			return ;
}

int	ft_export(t_env **env, char **str, int i)
{
	t_env		*tempv;
	char		**new_env;

	tempv = *env;
	if (!check_varexp(str))
	{
		new_env = ft_split(str, '=');
		if (!new_env)
			return (1);
		if (env_lookup(env, str) == 1)
			insert_env(tempv, new_env[0], new_env[1]);
		else if (env_lookup(env, str) == 2)
			update_env(tempv, new_env[1]);
	}
	return (0);
}
