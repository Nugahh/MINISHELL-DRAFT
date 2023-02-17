/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:41 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/17 18:55:17 by fwong            ###   ########.fr       */
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
	store = calloc(strlen(cmd), sizeof(int));
	while (cmd[i])
	{
		if (cmd[i] == '\'' && state == SINGLE)
			state = DEFAULT;
		else if (cmd[i] == '\'' && state == DEFAULT)
			state = SINGLE;
		if (cmd[i] == '\"' && state == DEFAULT)
			state = DOUBLE;
		else if (cmd[i] == '\"' && state == DOUBLE)
			state = DEFAULT;
 		// if (state != DEFAULT && cmd[i] == 32)
		// 	i++;
		store[cmd[i]] = state;
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
	end = 0;
	while (cmd[i])
	{
		start = i;
		printf("cmd[%d] = %d\n", i, store[cmd[i]]);
		if (cmd[i] != 32 && cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && store[cmd[i]] == DEFAULT)
		{
		printf("cmd[%d] = %d\n", i, store[cmd[i]]);

			i++;
			end++;
		}
		start = i;
		if (store[cmd[i]] != DEFAULT)
		{
		printf("cmd[%d] = %d\n", i, store[cmd[i]]);

			i++;
			end++;			
		}
		if (cmd[i] == 32 && store[cmd[i]] == DEFAULT)
			insert(head, cmd, start, end - start);
		i++;
		end++;
	}
}

// void f_split(char *cmd, t_token **head)
// {
// 	int state;
// 	int	end;
// 	int	start;
// 	int	i;
	
// 	i = 0;
// 	state = DEFAULT;
// 	while (cmd[i])
// 	{
// 		start = i;
// 		if (cmd[i] == '\'' && state != DOUBLE)
// 		{
// 			i++;
// 			state = SINGLE;
// 		}
// 		if (cmd[i + 1] == '\'' && state == SINGLE)
// 			state = DEFAULT;
// 		if (cmd[i] == '\"' && state != SINGLE)
// 		{
// 			i++;
// 			state = DOUBLE;
// 		}
// 		if (cmd[i + 1] == '\"' && state == DOUBLE)
// 			state = DEFAULT;
// 		if (state != DEFAULT && cmd[i] == 32)
// 			i++;
// 		end = 0;
// 		;
// 		while (cmd[i] && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
// 		{
// 			if (cmd[i] == ' ' && state == DEFAULT)
// 				break ;
// 			if (ft_check_end_state(cmd[i], state))
// 			{
// 				state = DEFAULT;
// 				i++;
// 				end++;
// 				break ;
// 			}
// 			i++;
// 			end++;
// 		}
// 		// if (cmd[i + 1] == '\0')
// 		// 	return ;
// 		if ((state == DEFAULT) && cmd[i] == 32 || cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '\0')
// 		{
// 			if (end > 0)
// 				insert(head, cmd, start, end);
// 			end = 0;
// 		}
// 		i++;
// 	}
// }

int main(int ac, char **av) 
{
	t_token *head = NULL;
	(void)ac;
	(void)av;
	ft_split_test("0123 \"\" \'123\"\'", &head);
	// int *store = ft_store_state("0123 \"\" \'123\"\'");
	// for (int i = 0; i < 20; i++)
	// 	printf("%d = %d\n", i, store[i]);
	printstr(head);
	return 0;
}