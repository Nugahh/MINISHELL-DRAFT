#include "../LIB/minishell.h"

void	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_varexp(char *str)
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

void	update_env(t_env *tempv, char *value)
{
	if (tempv->value)
		free(tempv->value);
	tempv->value = ft_strdup(value);
	if (!tempv->value)
		return ;
}

int	env_lookup(t_env **env, char *str)
{
	t_env	*tempv;

	tempv = *env;
	while (tempv)
	{
		if (ft_strcmp(tempv->name, str) == 0)
			return (1);
		tempv = tempv->next;
	}
	return (0);
}

int	ft_export(t_env **env, char **str)
{
	t_env		*tempv;
	char		**new_env;

	tempv = *env;
	if (check_varexp(str[1]) == 0)
	{
		new_env = ft_split(str[1], '=');
		if (!new_env)
			return (1);
		if (env_lookup(env, new_env[0]) == 0)
			insert_env(env, new_env[0], new_env[1]);
		else if (env_lookup(env, new_env[0]) == 1)
			update_env(tempv, new_env[1]);
		add_env_struct(env);
	}
	return (0);
}
