/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPLITS.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:22:51 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/15 17:46:30 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

t_token *create(char *str, int start, int j)
{
	t_token *yo;
	int	x;

	x = 0;
	yo = malloc(sizeof(t_token));
	yo->value = malloc(sizeof(char) * (j + 1));
	while (x <= j)
	{
		yo->value[x] = str[start];
		start++;
		x++;
	}
	yo->type = START;
	yo->next = NULL;
	return (yo);
}

void	insert(t_token **head, char *str, int start, int j)
{
	t_token *new;
	t_token *temp;

	new = create(str, start, j);
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	first_split(char *cmd, t_token **head)
{
	int state;
	int	i;
	int	j;
	int start;
	
	i = 0;
	state = DEFAULT;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			state = DOUBLE;
			j = 0;
			start = i;
			while (cmd[i] && cmd[i + 1] != '\"')
			{
				j++;
				i++;
			}
			if (cmd[i + 1] == '\"')
			{
				j++;
				i++;
			}
			i++;
			insert(head, cmd, start, j);
		}
		else if (cmd[i] == '\'')
		{
			state = SINGLE;
			start = i;
			j = 0;
			while (cmd[i] && cmd[i + 1] != '\'')
			{
				i++;
				j++;
			}
			if (cmd[i + 1] == '\'')
			{
				i++;
				j++;
			}
			i++;
			insert(head, cmd, start, j);
		}
		else if (cmd[i] != '\'' || cmd[i] != '\"')
		{
			state = DEFAULT;
			start = i;
			j = 0;
			while (cmd[i] && cmd [i + 1] != '\'' && cmd[i + 1] != '\"')
			{
				i++;
				j++;
			}
			insert(head, cmd, start, j);
		}
		if (cmd[i] == '\0')
			return ;
		i++;
	}
}

void	printstr(t_token *head)
{
	t_token *temp = head;
	while (temp)
	{
		printf("node:%s+ ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	t_token *head = NULL;
	char cmd[] = "echo \'hello\' |  \"\'yo\'\"";
	first_split(cmd, &head);
	printstr(head);
	// for (int i = 0; cmd[i]; i++)
	// {
	// 	printf("[%c] -> %d\n", cmd[i], state[i]);
	// }
}
