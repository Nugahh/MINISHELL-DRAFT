#include "../LIB/minishell.h"

void	ft_delete_redir(t_token *token, int count)
{
	t_token *temp;

	temp = token;
	while (temp && count > 1)
	{
		if (temp->type == RIN || temp->type == ROUT || temp->type == DROUT)
		{
			free(temp->value);
			free(temp->next->value);
			count--;
		}
		temp = temp->next;
	}
}
int	ft_count_redir(t_token **token)
{
	t_token *temp;
	t_token *temp2;
	int		count;

	temp = *token;
	temp2 = *token;
	while (temp)
	{
		while (temp2)
		{
			count = 0;
			if (temp2->type == RIN || temp->type == ROUT || temp->type == DROUT)
				count++;
			if (temp2->type == PIPE)
			{
				ft_delete_redir(temp, count);
				temp = temp2;
				break ;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return (0);
}
