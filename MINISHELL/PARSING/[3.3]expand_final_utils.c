/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3.3]expand_final_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:52:49 by fwong             #+#    #+#             */
/*   Updated: 2023/03/14 20:50:37 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

int	remove_first_quote(int stateBefore, int state)
{
	if ((state == SINGLE || state == DOUBLE)	
		&& stateBefore == DEFAULT)
		return (1);
	return (0);
}
int	count_second_quote(int state, int stateBefore)
{
	if (state == DEFAULT
		&& (stateBefore == SINGLE || stateBefore == DOUBLE))
		return (1);
	return (0);
}
int	count_removed_quotes(t_token *token, int stateBefore)
{
	int	i;
	int	count;
	int	state;

	i = 0;
	count = 0;
	state = DEFAULT;
	if (token->value[0] == '\'' || token->value[0] == '\"')
	{
		if (token->value[0] == '\'')
		{
			state = SINGLE;
			stateBefore = SINGLE;
			i++;
			count++;
		}
		else if (token->value[0] == '\"')
		{
			state = DOUBLE;
			stateBefore = DOUBLE;
			i++;
			count++;
		}
	}
	while (token->value[i])
	{
		state = ft_get_state(token->value[i], state);
		if (remove_first_quote(stateBefore, state))
		{
			stateBefore = ft_get_state(token->value[i], stateBefore);
			count++;
		}
		else if (count_second_quote(state, stateBefore))
		{
			stateBefore = ft_get_state(token->value[i], stateBefore);
			count++;
		}
		i++;
	}
	printf("count: %d\n", count);
	return (count);
}

