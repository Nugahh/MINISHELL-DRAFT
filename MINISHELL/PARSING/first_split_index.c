/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:41 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/18 20:10:56 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

/* void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && ((count * size) / count != size))
		return (0);
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (count * size));
	return (ptr);
} */

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

// int	*ft_store_state(char *cmd)
// {
// 	int i;
// 	int	state;
// 	int *store;

// 	i = 0;
// 	state = DEFAULT;
// 	store = ft_calloc(strlen(cmd), sizeof(int));
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' && state == SINGLE)
// 			state = DEFAULT;
// 		else if (cmd[i] == '\'' && state == DEFAULT)
// 			state = SINGLE;
// 		if (cmd[i] == '\"' && state == DEFAULT)
// 			state = DOUBLE;
// 		else if (cmd[i] == '\"' && state == DOUBLE)
// 			state = DEFAULT;
// 		store[i] = state;
// 		printf("store[%d] = %d\n",i,  store[i]);
// 		i++;
// 	}
// 	return (store);
// }

// int	*ft_store_state(char *cmd)
// {
// 	int i;
// 	int	state;
// 	int *store;

// 	i = 0;
// 	state = DEFAULT;
// 	store = ft_calloc(strlen(cmd), sizeof(int));
// 	while (cmd[i])
// 	{
// 		if (state == DEFAULT)
// 			if (cmd[i] == '\'')
// 				state = SINGLE;
// 			else if (cmd[i] == '\"')
// 				state = DOUBLE;
// 		else if (state == SINGLE)
// 			if (cmd[i] == '\'')
// 				state = DEFAULT;
// 		else if (state == DOUBLE)
// 			if (cmd[i] == '\"')
// 				state = DEFAULT;
// 		store[i] = state;
// 		// printf("store[%d] = %d\n",i,  store[i]);
// 		i++;
// 	}
// 	return (store);
// }

int	ft_store_state(char c, int state)
{
	if (state == DEFAULT)
	{
		if (c == '\'')
			state = SINGLE;
		else if (c == '\"')
			state = DOUBLE;	
	}
	else if (state == SINGLE)
	{
		if (c == '\'')
			state = DEFAULT;
	}
	else if (state == DOUBLE)
	{
		if (c == '\"')
			state = DEFAULT;
	}
	return (state);
}

void	ft_split_test(char *cmd, t_token **head)
{
	int state;
	int	end;
	int	start;
	int	i;

	i = 0;
	end = strlen(cmd);
	start = 0;
	state = DEFAULT;
	while (i < end)
	{
		// printf("i = %d -- c = %c -- state = %d\n", i, cmd[i], state);
//		printf("i = %d -- c = %c\n", i, cmd[i]);
		state = ft_store_state(cmd[i], state);
		if (state == DEFAULT && i < end && cmd[i] == 32)
		{
			while (cmd[i] == 32)
				i++;
			start = i;
		}
		else
			i++;
		// printf("cmd[%d] = %d\n", i, cmd[i]);
		if (state == DEFAULT && cmd[i] == 32)
		{
//			printf("start = %d -- end = %d\n", start, i);
			insert(head, cmd, start, i - start - 1);
			start = i + 1;
		}
		else if (i + 1 == end)
			insert(head, cmd, start, i - start);
	}
}

// void	ft_split_test(char *cmd, t_token **head)
// {
// 	int state;
// 	int	end;
// 	int	start;
// 	int	i;
// 	int	*store;

// 	i = 0;
// 	store = ft_store_state(cmd);
// 	end = 0;
// 	while (cmd[i])
// 	{
// 			// printf("cmd x[%d] = %c\n", i, cmd[i]);
// 		while (cmd[i] != '\0' && cmd[i] == 32 && store[i] == DEFAULT)
// 		{
// 			// printf("cmd h[%d] = %c\n", i, cmd[i]);
// 			end++;
// 			i++;
// 		}
// 		start = i;
// 		while (cmd[i] && cmd[i] != 32 && cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '|' && store[i] == DEFAULT)
// 		{
// 			// printf("cmd [%d] = %c\n", i, cmd[i]);
// 			i++;
// 			end++;
// 		}
// 		while (store[i] == SINGLE || store[i] == DOUBLE)
// 		{
// 			// printf("cmd[%d] = %c\n", i, cmd[i]);
// 			i++;
// 			end++;
// 			if (cmd[i] == '\"' && store[i] != SINGLE)
// 			{
// 				end++;	
// 				i++;
// 			}
// 			if (cmd[i] == '\'' && store[i] != DOUBLE)
// 			{
// 				end++;	
// 				i++;
// 			}
// 		}
// 		// if (cmd[i] && cmd[i] != 32 && cmd[i + 1] == '\0')
// 		// 	return ;
// 		if (cmd[i] == '\0')
// 		 	insert(head, cmd, start, end - start - 1);
// 		if (cmd[i] || cmd[i] == 32 && store[i] == DEFAULT)
// 		{
// //			printf("je rentre \n");			
// 			insert(head, cmd, start, end - start - 1);
// 		}
// 		printf("cmd ff[%d] = %d\n", i, cmd[i]);
// 		i++;
// 		printf("cmd ff[%d] = %d\n", i, cmd[i]);
// 		end++;
// 	}
// }

/* int main(int ac, char **av) 
{
	t_token *head = NULL;
	(void)ac;
	ft_split_test(av[1], &head);
	// int *store = ft_store_state("0123 \"\" \'123\"\'");
	// for (int i = 0; i < 20; i++)
	// 	printf("%d = %d\n", i, store[i]);
	printstr(head);
	return 0;
} */
//"   echo he    llo haha \"lo   l\"     "