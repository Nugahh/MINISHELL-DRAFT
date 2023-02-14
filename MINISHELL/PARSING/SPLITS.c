/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPLITS.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:22:51 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/14 17:06:41 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

int	get_state(char *cmd)
{
	int state;
	int	i;

	i = 0;
	state = DEFAULT;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			printf("[%c] -> 2 = %d\n", cmd[i], state);
			state = DOUBLE;
			while (cmd[i] && cmd[i + 1] != '\"')
			{
				// remplir node ici
				printf("[%c] -> 2 = %d\n", cmd[i], state);
				state = DOUBLE;
				i++;
			}
			if (cmd[i + 1] == '\"')
			{
				// remplir node ici
				printf("[%c] -> 2bis = %d\n", cmd[i], state);
				state = DEFAULT;
				i++;
			}
		}
		if (cmd[i] == '\'')
		{
			state = SINGLE;
			printf("[%c] -> ICI = %d\n", cmd[i + 1],  state);
			while (cmd[i] && cmd[i + 1] != '\'')
			{
				// remplir node ici
				printf("[%c] -> 1 = %d\n", cmd[i + 1],  state);
				state = SINGLE;
				i++;
			}
			if (cmd[i + 1] == '\'')
			{
				// remplir node ici
				printf("[%c] -> 1bis = %d\n",cmd[i + 1],  state);
				state = DEFAULT;
				i++;
			}
		}
		printf("[%c] -> def = %d\n", cmd[i], state);
		i++;
	}
	/* if state = DOUBLE || SINGLE return error newline
	and free node */
	return (state);
}

char	*first_split(char *cmd)
{
	int		i;
	char	*node;

	i = 0;
	node = NULL;
	while (cmd[i] && cmd[i] != ' ')
	{
		while (get_state(cmd) == DEFAULT)
		{
			node[i] = cmd [i];
			i++;
			return (node);
		}
		while (get_state(cmd) == SINGLE)
		{
			node[i] = cmd [i];
			i++;
			return (node);
		}
		while (get_state(cmd) == DOUBLE)
		{
			node[i] = cmd [i];
			i++;
			return (node);
		}	
	}
	return (node);
}

int main()
{
	char cmd[] = "echo \'hello\"\'\'\'\'\' \"test\'\'\"  dsdsfd";
	get_state(cmd);
	// for (int i = 0; cmd[i]; i++)
	// {
	// 	printf("[%c] -> %d\n", cmd[i], state[i]);
	// }
}