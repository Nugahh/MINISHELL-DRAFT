/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]expand_final.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:52:49 by fwong             #+#    #+#             */
/*   Updated: 2023/03/17 01:36:39 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

static int	first_char_is_quote(t_token *token)
{
	if (token->value[0] == '\'')
		return (SINGLE);
	else if (token->value[0] == '\"')
		return (DOUBLE);
	return (-1);
}

int	remove_quotes_in_node(int state, int stateBefore)
{
	if (remove_first_quote(stateBefore, state))
		return (1);
	else if (remove_second_quote(state, stateBefore))
		return (1);
	return (0);
}

char	*check_node(t_token *token, int i, int j, int stateBefore)
{
	int		state;
	int		len;
	char	*copy_token;
	
	state = DEFAULT;
	len = ft_strlen(token->value);
	copy_token = ft_calloc((len - c_rq(token, stateBefore)) + 2, sizeof(char));
	if (token->value[0] == '\'' || token->value[0] == '\"')
	{
		state = first_char_is_quote(token);
		stateBefore = state;
		j++;
	}
	while (token->value[j])
	{
		state = ft_get_state(token->value[j], state);
		if (remove_quotes_in_node(state, stateBefore) == 1)
		{
			stateBefore = ft_get_state(token->value[j], stateBefore);
			j++;
		}
		else
			copy_token[i++] = token->value[j++];
	}
	return (copy_token);
}

int	remove_quotes(t_token **token)
{
	t_token	*temp;
	char	*copy_token;

	temp = *token;
	if (!temp)
		return (1);
	while (temp)
	{
		copy_token = check_node(temp, 0, 0, -1);
		free(temp->value);
		temp->value = ft_strdup(copy_token);
		free(copy_token);
		temp = temp->next;
	}
	return (0);
}
