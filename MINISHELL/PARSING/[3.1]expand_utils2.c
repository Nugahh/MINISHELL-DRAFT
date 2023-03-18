#include "../LIB/minishell.h"

int	is_allowed_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	write_env_value(int *len, t_env *env, char *temp, int i)
{
	int		j;

	j = 0;
	*len += ft_strlen(env->value);
	while (env->value[j])
		temp[i++] = env->value[j++];
	return (*len);
}
// int	write_status(int i, char *temp, char *copyToken)
// {
// 	char	*status;
// 	int		j;

// 	j = 0;
// 	status = ft_itoa(g_error);
// 	while (status[j])
// 		temp[i++] = status[j++];
// 	free(status);
// 	return (len_status(g_error));
// }