/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:41 by khuynh            #+#    #+#             */
<<<<<<<< HEAD:MINISHELL/TRASH/first_split.c
/*   Updated: 2023/02/19 22:40:44 by khuynh           ###   ########.fr       */
========
/*   Updated: 2023/02/20 20:06:31 by fwong            ###   ########.fr       */
>>>>>>>> 7fc6933 (first step done):.history/MINISHELL/PARSING/[1] first_split_20230220200630.c
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

int	ft_skip_spaces(char *cmd, int i)
{
	while (cmd[i] == 32)
		i++;
	return (i);
}

int	ft_check_spaces_and_not_operator(char *cmd, int i)
{
	if ((cmd[i] == 32 && !is_operator(cmd[i - 1]))
		|| (is_operator(cmd[i]) && !is_operator(cmd[i - 1])))
		return (1);
	return (0);
}

int	insert_and_init_new_start(char *cmd, t_token **head, int i, int start)
{
	insert(head, cmd, start, i - start - 1);
	start = i + 1;
	return (start);
}

void	ft_split_test(char *cmd, t_token **head, int i, int start)
{
	int	state;
	int	end;

	end = ft_strlen(cmd);
	state = DEFAULT;
	while (cmd[i])
	{
<<<<<<<< HEAD:MINISHELL/TRASH/first_split.c
		state = ft_store_state(cmd[i], state);
		if (state == DEFAULT && i < end && cmd[i] == 32)
========
		state = ft_get_state(cmd[i], state);
		if (state == DEFAULT && (cmd[i] == 32 || is_operator(cmd[i])))
>>>>>>>> 7fc6933 (first step done):.history/MINISHELL/PARSING/[1] first_split_20230220200630.c
		{
			i = ft_skip_spaces(cmd, i);
			start = i;
<<<<<<<< HEAD:MINISHELL/TRASH/first_split.c
		}
		else
			i++;
		if (state == DEFAULT && cmd[i] == 32)
		{
			insert(head, cmd, start, i - start - 1);
			start = i + 1;
		}
		else if (i + 1 == end)
========
			if (is_operator(cmd[i]))
			{
				i = check_insert_op_and_init(head, cmd, start, i);
				start = i;
			}
		}
		else
			i++;
		if (state == DEFAULT && (ft_check_spaces_and_not_operator(cmd, i)))
			start = insert_and_init_new_start(cmd, head, i, start);
		else if (i == end && !is_operator(cmd[i - 1]) && cmd[i - 1] != ' ')
>>>>>>>> 7fc6933 (first step done):.history/MINISHELL/PARSING/[1] first_split_20230220200630.c
			insert(head, cmd, start, i - start);
	}
}
