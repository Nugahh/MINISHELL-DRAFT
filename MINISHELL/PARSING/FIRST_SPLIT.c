/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FIRST_SPLIT.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:41 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/16 18:31:23 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

t_token *create(char *str, int end)
{
	t_token *yo;
	int	x;

	x = 0;
	yo = malloc(sizeof(t_token));
	yo->value = malloc(sizeof(char) * (end + 1));
	while (x <= end)
	{
		yo->value[x] = *str;
		str++;
		x++;
	}
	yo->type = START;
	yo->next = NULL;
	return (yo);
}

void	insert(t_token **head, char *str, int end)
{
	t_token *new;
	t_token *temp;

	new = create(str, end);
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

void f_split(char *cmd, t_token **head)
{
	int state;
	int	end;
	
	end = 0;
	state = DEFAULT;
	while (*cmd)
	{
		if (*cmd == '\'' && state != DOUBLE)
			state = SINGLE;
		if (*cmd + 1 == '\'' && state == SINGLE)
			state = DEFAULT;
		if (*cmd == '\"' && state != SINGLE)
			state = DOUBLE;
		if (*cmd + 1 == '\"' && state == DOUBLE)
			state = DEFAULT;
		if (state != DEFAULT && *cmd == 32)
			cmd++;
		while (*cmd && *cmd != 32 && *cmd != '|' && *cmd != '<' && *cmd != '>')
		{
			cmd++;
			end++;
		}
		if ((state == DEFAULT) && *cmd == 32 || *cmd == '|' || *cmd == '<' || *cmd == '>' || *cmd == '\0')
		{
			insert(head, cmd - end, end);
			end = 0;
		}
		end++;
		cmd++;
	}
}

int main(int ac, char **av) 
{
	t_token *head = NULL;
	(void)ac;
	(void)av;
	f_split("echo \"hello\" allo", &head);
	printstr(head);
	return 0;
}