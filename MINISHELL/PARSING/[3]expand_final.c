
#include "../LIB/minishell.h"

int	count_second_quote(t_token *token, int i, int state)
{
	if ((state == SINGLE || state == DOUBLE)
		&& (ft_get_state(token->value[i + 1], state) == DEFAULT))
		return (1);
	return (0);
}

int	remove_second_quote(int state, int stateBefore)
{
	if ((stateBefore == SINGLE || stateBefore == DOUBLE)
		&& state == DEFAULT)
		return (1);
	return (0);
}
int	first_char_is_quote(t_token *token)
{
	if (token->value[0] == '\'')
		return (SINGLE);
	else if (token->value[0] == '\"')
		return (DOUBLE);
	return (-1);
}
int	remove_quotes_in_node(t_token *token, int j, int state, int stateBefore)
{
	if (remove_first_quote(token, j, stateBefore))
		return (1);
	else if (remove_second_quote(state, stateBefore))
		return (1);
	return (0);
}
char	*check_node(t_token *token, int i, int j, int stateBefore)
{
	int		state;
	int		len;
	char	*copyToken;
	
	state = DEFAULT;
	len = ft_strlen(token->value);
	copyToken = ft_calloc((len - count_removed_quotes(token)) + 2, sizeof(char));
	if (token->value[0] == '\'' || token->value[0] == '\"')
	{
		state = first_char_is_quote(token);
		stateBefore = state;
		j++;
	}
	while (i <= len - count_removed_quotes(token))
	{
		if (remove_quotes_in_node(token, j, state, stateBefore) == 1)
		{
			stateBefore = ft_get_state(token->value[j], stateBefore);
			j++;
		}
		else
			copyToken[i++] = token->value[j++];
		state = ft_get_state(token->value[j], state);
	}
	return (copyToken);
}
int	remove_quotes(t_token **token)
{
	t_token	*temp;
	char	*copyToken;

	temp = *token;
	if (!temp)
		return (1);
	while (temp)
	{
		copyToken = check_node(temp, 0, 0, DEFAULT);
		free(temp->value);
		temp->value = ft_strdup(copyToken);
		free(copyToken);
		temp = temp->next;
	}

	return (0);
}
