/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:41 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/18 02:01:39 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

t_token *create(char *str, int start, int end)
{
	t_token *yo;
	int	x;

	x = 0;
	yo = malloc(sizeof(t_token));
	yo->value = malloc(sizeof(char) * (end + 1));
	while (x <= end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->type = START;
	yo->next = NULL;
	return (yo);
}

void	insert(t_token **head, char *str, int start, int end)
{
	t_token *new;
	t_token *temp;

	new = create(str, start, end);
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

bool ft_check_end_state(char c, int state)
{
	if (c == '\'' && state != DOUBLE && state != DEFAULT)
		return (true);
	if (c == '\"' && state != SINGLE && state != DEFAULT)
		return (true);
	return (false);
}

int	*ft_store_state(char *cmd)
{
	int i;
	int	state;
	int *store;

	i = 0;
	state = DEFAULT;
	store = calloc(strlen(cmd + 2), sizeof(int));
	while (cmd[i])
	{
		printf("state = %d\n", store[i]);
		if (cmd[i] == '\'' && state == SINGLE)
			state = DEFAULT;
		else if (cmd[i] == '\'' && state == DEFAULT)
			state = SINGLE;
		if (cmd[i] == '\"' && state == DEFAULT)
			state = DOUBLE;
		else if (cmd[i] == '\"' && state == DOUBLE)
			state = DEFAULT;
		store[i] = state;
		i++;
	}
	return (store);
}

void	ft_split_test(char *cmd, t_token **head)
{
	int state;
	int	end;
	int	start;
	int	i;
	int	*store;

	i = 0;
	store = ft_store_state(cmd);
	for (int x = 0; x < 12; x++)
		printf("store[%d] = %d\n", x, store[x]);
	end = 0;
	while (cmd[i])
	{
			// printf("cmd x[%d] = %c\n", i, cmd[i]);

		while (cmd[i] != '\0' && cmd[i] == 32 && store[i] == DEFAULT)
		{
			printf("cmd h[%d] = %c\n", i, cmd[i]);
			end++;
			i++;
		}
		start = i;
		while (cmd[i] && cmd[i] != 32 && cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && store[i] == DEFAULT)
		{
			printf("cmd [%d] = %c\n", i, cmd[i]);
			i++;
			end++;
		}
		while (store[i] == SINGLE || store[i] == DOUBLE)
		{
			printf("cmd[%d] = %c\n", i, cmd[i]);
			i++;
			end++;
			if (cmd[i] == '\"' && store[i] != SINGLE)
			{
				end++;	
				i++;
			}
			if (cmd[i] == '\'' && store[i] != DOUBLE)
			{
				end++;	
				i++;
			}
		}
		if (cmd[i] && cmd[i] != 32 && cmd[i + 1] == '\0')
			return ;
		if (cmd[i] == '\0')
			insert(head, cmd, start, end - start - 1);
		if (cmd[i] && cmd[i] == 32 && store[i] == DEFAULT)
		{
//			printf("je rentre \n");			
			insert(head, cmd, start, end - start - 1);
		}
		i++;
		end++;
	}
}

int main(int ac, char **av) 
{
	t_token *head = NULL;
	(void)ac;
	(void)av;
	ft_split_test("echo \"lo   l\" caca  ", &head);
	// int *store = ft_store_state("0123 \"\" \'123\"\'");
	// for (int i = 0; i < 20; i++)
	// 	printf("%d = %d\n", i, store[i]);
	printstr(head);
	return 0;
}
//"   echo he    llo haha \"lo   l\"     "