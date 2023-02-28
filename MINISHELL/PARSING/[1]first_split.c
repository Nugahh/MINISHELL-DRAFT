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

static int	insert_and_init_new_start(char *cmd, t_token **head, int i, int start)
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

int	ft_first_split(char *cmd, t_token **head, int i, int start)
{
	int	state;
	int	end;

	end = ft_strlen(cmd);
	state = DEFAULT;
	while (cmd[i])
	{
		state = ft_get_state(cmd[i], state);
		if (state == DEFAULT && (cmd[i] == 32 || is_operator(cmd[i])))
		{
			if (skip_spaces_and_insert_op((int *[2]){&i, &start}, cmd, head))
				return (1);
		}
		else
			i++;
		if (state == DEFAULT && (ft_check_spaces_and_not_operator(cmd, i)))
		{
			start = insert_and_init_new_start(cmd, head, i, start);
			if (start == -1)
				return (1);
		}
		else if (i == end && !is_operator(cmd[i - 1]) && cmd[i - 1] != ' ')
		{
			if (insert(head, cmd, start, i - start))
				return (1);
		}
	}
	return (assign_type(head));
}
