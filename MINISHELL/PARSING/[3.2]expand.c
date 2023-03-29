#include "../LIB/minishell.h"

int	expanded_var(char *copyToken, int **i_j, t_env **env, char *temp)
{
	t_env	*temp_env;
	int		len;
	int		len_e;

	len = 0;
	temp_env = *env;
	len_e = len_before_env(copyToken, *i_j[0]) + len_env(copyToken, i_j);
	while (temp_env && len_e > 0)
	{
		if (ft_strncmpBis(copyToken, temp_env->name, \
		*i_j[0] + 1, len_e + 1) == 0)
			break ;
		temp_env = temp_env->next;
	}
	if (temp_env && len_e > 0)
		write_env_value(&len, temp_env, temp, *i_j[1]);
	return (len);
}

char	*token_expanded(char *temp, int **i_j, char *copyToken, t_env **env)
{
	int		state;

	state = DEFAULT;
	while (copyToken[*i_j[0]])
	{
		state = ft_get_state(copyToken[*i_j[0]], state);
		if (copyToken[*i_j[0]] == '$' && is_allowed_char(copyToken[*i_j[0] + 1])
			&& (state == DEFAULT || state == DOUBLE))
		{
			*i_j[1] += expanded_var(copyToken, i_j, env, temp);
			*i_j[0] += len_env(copyToken, i_j) + 1;
		}
		else
			temp[(*i_j[1])++] = copyToken[(*i_j[0])++];
	}
	temp[*i_j[1]] = '\0';
	return (temp);
}

char	*fill_expand(char *copyToken, t_env **env)
{
	char	*temp;
	int		i;
	int		k;
	int		j;

	k = 0;
	j = 0;
	i = len_token_expanded(copyToken, env);
	temp = ft_calloc(i + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp = token_expanded(temp, (int *[2]){&k, &j}, copyToken, env);
	return (temp);
}

int	call_expand(t_token *token, t_env **env)
{
	int		i;
	int		state;
	char	*copy_token;

	i = -1;
	state = DEFAULT;
	while (token->value && token->value[++i])
	{
		state = ft_get_state(token->value[i], state);
		if (token->value[i] == '$' && is_allowed_char(token->value[i + 1])
			&& (state == DEFAULT || state == DOUBLE))
		{
			copy_token = ft_strdup(token->value);
			free(token->value);
			token->value = fill_expand(copy_token, env);
			if (!token->value)
				return (free(copy_token), 1);
			free(copy_token);
			break ;
		}
	}
	return (0);
}

int	expand(t_token **token, t_env **env)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		if (call_expand(temp, env) == 1)
			return (1);
		temp = temp->next;
	}
	return (remove_quotes(token));
}
