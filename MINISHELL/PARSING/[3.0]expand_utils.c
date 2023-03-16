#include "../LIB/minishell.h"

int len_env(char *str, int **i_j)
{
	int len;
	int	i;

	i = *i_j[0];
	len = 0;
	if (str[i] == '?')
		return (1);
	while (str[i+ 1] && is_allowed_char(str[i+ 1]))
	{
		len++;
		i++;
	}
	return (len);
}
int len_before_env(char *str, int i)
{
	int len;

	len = 0;
	while (str[len] && len < i)
		len++;
	return (len);
}
int len_status(int status)
{
	int len;

	len = 0;
	if (status == 0)
		return (1);
	while (status)
	{
		status /= 10;
		len++;
	}
	return (len);
}

int len_env_expanded(char *copyToken, int **i_j, int len_env, t_env **env)
{
	t_env *tempEnv;
	int len;

	len = 0;
	tempEnv = *env;
	// if (copyToken[i] == '?')
	// 	return (len_status(g_error));
	while (tempEnv)
	{
		if (ft_strncmpBis(copyToken, tempEnv->name, *i_j[0] + 1, len_env) == 0)
			break;
		tempEnv = tempEnv->next;
	}
	if (tempEnv)
		len += ft_strlen(tempEnv->value);
	return (len);
}
int len_token_expanded(char *copyToken, t_env **env)
{
	int i;
	int state;
	int len;

	len = 0;
	i = 0;
	state = DEFAULT;
	while (copyToken[i])
	{
		state = ft_get_state(copyToken[i], state);
		if (copyToken[i] == '$' && is_allowed_char(copyToken[i + 1]) && (state == DEFAULT || state == DOUBLE))
		{
			len += len_env_expanded(copyToken, ((int *[2]){&i, 0}), len_env(copyToken, (int *[2]){&i, 0}), env);
			i += len_env(copyToken, (int *[2]){&i, 0}) + 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
