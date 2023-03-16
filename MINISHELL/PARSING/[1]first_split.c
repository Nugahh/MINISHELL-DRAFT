/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]first_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:47:09 by fwong             #+#    #+#             */
/*   Updated: 2023/03/16 20:20:09 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

static int	ft_skip_spaces(char *cmd, int i)
{
	while (cmd[i] == 32)
		i++;
	return (i);
} 

static int	ft_check_spaces_and_not_operator(char *cmd, int i)
{
	if ((cmd[i] == 32 && !is_operator(cmd[i - 1]))
		|| (is_operator(cmd[i]) && !is_operator(cmd[i - 1])))
		return (1);
	return (0);
}

static int	insert_and_init_new_start(char *cmd, t_token **head, int i, \
																int start)
{
	if (insert(head, cmd, start, i - start - 1))
		return (-1);
	start = i + 1;
	return (start);
}

static int skip_spaces_and_insert_op(int **arr, char *cmd, t_token **head)
{
	*arr[0] = ft_skip_spaces(cmd, *arr[0]);
	*arr[1] = *arr[0];
	if (is_operator(cmd[*arr[0]]))
	{
		*arr[0] = check_insert_op_and_init(head, cmd, *arr[1], *arr[0]);
		if (*arr[0] == -1)
			return (1);
		*arr[1] = *arr[0];
	}
	return (0);
}

int	ft_first_split(char *cmd, t_token **head, int **s_i, int start)
{
	while (cmd[*s_i[1]])
	{
		*s_i[0] = ft_get_state(cmd[*s_i[1]], *s_i[0]);
		if (*s_i[0] == DEFAULT && (cmd[*s_i[1]] == ' ' || is_operator(cmd[*s_i[1]])))
		{
			if (skip_spaces_and_insert_op((int *[2]){&*s_i[1], &start}, cmd, head))
				return (1);
		}
		else
			(*s_i[1])++;
		if (*s_i[0] == DEFAULT && (ft_check_spaces_and_not_operator(cmd, *s_i[1])))
		{
			start = insert_and_init_new_start(cmd, head, *s_i[1], start);
			if (start == -1)
				return (1);
		}
		else if (*s_i[1] == ft_strlen(cmd) && !is_operator(cmd[*s_i[1] - 1]) && cmd[*s_i[1] - 1] != ' ')
		{
			if (insert(head, cmd, start, *s_i[1] - start))
				return (1);
		}
	}
	return (assign_type(head));
}
