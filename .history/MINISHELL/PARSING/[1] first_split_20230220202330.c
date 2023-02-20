#include "../LIB/minishell.h"

int	ft_get_state(char c, int state)
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
		state = ft_get_state(cmd[i], state);
		if (state == DEFAULT && (cmd[i] == 32 || is_operator(cmd[i])))
		{
			i = ft_skip_spaces(cmd, i);
			start = i;
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
			insert(head, cmd, start, i - start);
	}
}