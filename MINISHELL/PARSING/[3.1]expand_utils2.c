#include "../LIB/minishell.h"

int	is_allowed_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	len_env(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && is_allowed_char(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	len_status(int status)
{
	int	len;

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

int	len_env_expanded(char *str, int i, int len_env, t_env **env)
{
	t_env 		*tempEnv;
	int			len;

	len = 0;
	while (tempEnv)
	{
		if (ft_strncmp(tempEnv->name))
		i++;
	}
	return (len);
}