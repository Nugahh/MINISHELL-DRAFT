#include "../LIB/minishell.h"

int	remove_first_quote(int stateBefore, int state)
{
	if ((state == SINGLE || state == DOUBLE)	
		&& stateBefore == DEFAULT)
		return (1);
	return (0);
}
int	remove_second_quote(int state, int stateBefore)
{
	if (state == DEFAULT
		&& (stateBefore == SINGLE || stateBefore == DOUBLE))
		return (1);
	return (0);
}

static void	check_first_value(t_token *token, int **i_count, int *state, int *stateBefore)
{
	if (token->value[0] == '\'' || token->value[0] == '\"')
	{
		if (token->value[0] == '\'')
		{
			*state = SINGLE;
			*stateBefore = SINGLE;
			(*i_count[0])++;
			(*i_count[1])++;
		}
		else if (token->value[0] == '\"')
		{
			*state = DOUBLE;
			*stateBefore = DOUBLE;
			(*i_count[0])++;
			(*i_count[1])++;
		}
	}
}
int	count_removed_quotes(t_token *token, int stateBefore)
{
	int	i;
	int	count;
	int	state;

	i = 0;
	count = 0;
	state = DEFAULT;
	check_first_value(token, (int *[2]){&i, &count}, &state, &stateBefore);
	while (token->value[i])
	{
		state = ft_get_state(token->value[i], state);
		if (remove_first_quote(stateBefore, state))
		{
			stateBefore = ft_get_state(token->value[i], stateBefore);
			count++;
		}
		else if (remove_second_quote(state, stateBefore))
		{
			stateBefore = ft_get_state(token->value[i], stateBefore);
			count++;
		}
		i++;
	}
	return (count);
}

