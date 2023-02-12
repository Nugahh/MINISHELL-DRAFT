/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPLITS.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:22:51 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/12 18:22:12 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

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
			{
				status = DOUBLE;
				i++;
			}
		}
		else if (cmd[i] == '\'')
		{
			while (cmd[i] && cmd[i + 1] != '\'')
			{
				status = SINGLE;
				i++;
			}
		}
		i++;
	}
	return (status);
}

char	*first_split(char *cmd)
{
	int		i;
	char	*node;

	i = 0;
	node = NULL;
	while (status(cmd) == DEFAULT)
	{
		node[i] = cmd [i];
		i++;
		return (node);
	}
	while (status(cmd) == SINGLE)
	{
		node[i] = cmd [i];
		i++;
		return (node);
	}
	while (status(cmd) == DOUBLE)
	{
		node[i] = cmd [i];
		i++;
		return (node);
	}
	return (node);
}

int main()
{
	char cmd[] = "ls -la | echo \"hi\"";
	printf("%d\n", status(cmd));
}