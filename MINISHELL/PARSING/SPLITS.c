/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPLITS.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:22:51 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/08 23:32:27 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"


void	first_split(t_token *tok, char *cmd)
{
	int	i;

	i = 0;
	while (status(cmd) == DEFAULT)
	{
		tok->value = cmd[i];
		i++;
	}
	while (status(cmd) == SINGLE)
	{
		remplir tok->value d'un autre node ?? comment faire
	}
	while (status(cmd) == DOUBLE)
	{
		remplir tok->value d'un autre node ?? comment faire
	}
	
}

int	status(char *cmd)
{
	int	status;
	int	i;
	
	i = 0;
	status = DEFAULT;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			while (cmd[i] && cmd[i + 1] != '\"')
				status = DOUBLE;
		}
		else if (cmd[i] == '\'')
		{
			while (cmd[i] && cmd[i + 1] != '\'')
				status = SINGLE;
		}
		i++;
	}
	return (status);
}

