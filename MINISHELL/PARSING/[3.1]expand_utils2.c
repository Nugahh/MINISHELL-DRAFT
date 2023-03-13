#include "../LIB/minishell.h"

int	is_allowed_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
int	count_deleted_dollar(char *copyToken)
{
	int	i;
	int	state;
	int	count;

	i = 0;
	state = 0;
	count = 0;
	while (copyToken[i])
	{
		state = ft_get_state(copyToken[i], state);
		if (copyToken[i] == '$' && copyToken[i + 1] == '?'
			&& (state == DEFAULT || state == DOUBLE))
			count++;
		if (copyToken[i] == '$' && is_allowed_char(copyToken[i + 1]) == 1
			&& (state == DEFAULT || state == DOUBLE))
			count++;
		i++;
	}
	return (count);
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