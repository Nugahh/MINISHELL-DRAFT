#include "../LIB/minishell.h"

int	expanded_var(char *copyToken, int i, int j, int len_env, t_env **env, char *temp)
{
	t_env	*tempEnv;
	int		len;

	len = 0;
	tempEnv = *env;
	// if (copyToken[i] == '?')
	// 	return (write_status(i, temp, copyToken));
	while (tempEnv && len_env > 0)
	{
		if (ft_strncmpBis(copyToken, tempEnv->name, i, len_env + 1) == 0)
			break ;
		tempEnv = tempEnv->next;
	}
	if (tempEnv && len_env > 0)
		write_env_value(&len, tempEnv, temp, j);
	printf("len = %d\n", len);
	return (len);
}

char	*token_expanded(char *temp, char *copyToken, t_env **env)
{
	int		i;
	int		j;
	int		state;

	i = 0;
	j = 0;
	state = DEFAULT;
	while (copyToken[i])
	{
		state = ft_get_state(copyToken[i], state);
		if (copyToken[i] == '$' && is_allowed_char(copyToken[i + 1])
			&& (state == DEFAULT || state == DOUBLE))
		{
			j = j + expanded_var(copyToken, i + 1, j, len_before_env(copyToken, i) + len_env(copyToken, i + 1), env, temp);
			i += len_env(copyToken, i + 1) + 1;
		}
		else
			temp[j++] = copyToken[i++];
	}
	temp[j] = '\0';
	return (temp);
}
char	*fill_expand(char *copyToken, t_env **env)
{
	char *temp;
	int		i;

	i = len_token_expanded(copyToken, env);
	temp = ft_calloc(i + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp = token_expanded(temp, copyToken, env);
	return (temp);
}
int	call_expand(t_token *token, t_env **env)
{
	int		i;
	int		state;
	char	*copyToken;

	i = -1;
	state = DEFAULT;
	while (token->value && token->value[++i])
	{
		state = ft_get_state(token->value[i], state);
		if (token->value[i] == '$' && is_allowed_char(token->value[i + 1])
			&& (state == DEFAULT || state == DOUBLE))
		{
			copyToken = ft_strdup(token->value);
			free(token->value);
			token->value = fill_expand(copyToken, env);
			if (!token->value)
				return (free(copyToken), 1);
			free(copyToken);
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