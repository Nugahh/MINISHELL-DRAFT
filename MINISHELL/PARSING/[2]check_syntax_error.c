#include "../LIB/minishell.h"

int	ft_check_syntax_error(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == 7)
		return (display_error(&temp), 1);
	if (temp->type >= 3 && !temp->next)
		return (0);
	while (temp)
	{
		if (temp->type >= 3 && (!temp->next || temp->next->type >= 3))
			return (display_error(&temp), 1);
		temp = temp->next;
	}
	return (0);
}