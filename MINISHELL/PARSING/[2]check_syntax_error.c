#include "../LIB/minishell.h"

bool	ft_check_syntax_error(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == 7)
		return (display_error(&temp), false);
	while (temp)
	{
		if (temp->type >= 3 && (temp->next->type >= 3 || !temp->next))
			return (display_error(&temp), false);
		temp = temp->next;
	}
	return (true);
}