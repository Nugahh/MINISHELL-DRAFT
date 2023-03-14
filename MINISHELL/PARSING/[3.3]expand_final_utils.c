/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3.3]expand_final_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:52:49 by fwong             #+#    #+#             */
/*   Updated: 2023/03/14 04:19:53 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

int	count_removed_quotes(t_token *token)
{
	int	i;
	int	count;
	int	state;

	i = 0;
	count = 0;
	state = DEFAULT;
	if (token->value[0] == '\'' || token->value[0] == '\"')
			count++;
	while (token->value[i])
	{
		state = ft_get_state(token->value[i], state);
		if (remove_first_quote(token, i, state))
			count++;
		else if (count_second_quote(token, i, state))
			count++;
		i++;
	}
	return (count);
}

int	remove_first_quote(t_token *token, int i, int stateBefore)
{
	if (stateBefore == DEFAULT	
		&& ((ft_get_state(token->value[i], stateBefore) == SINGLE)
		|| (ft_get_state(token->value[i], stateBefore) == DOUBLE)))
		return (1);
	return (0);
}

