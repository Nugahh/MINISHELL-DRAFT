#include "../LIB/minishell.h"

void	ft_delete_redir(t_token *token, int count)
{
	t_token *temp;

	temp = token;
	while (temp && count > 1)
	{
		printf("temp->type: %d\n", temp->type);
		if (temp->type == RIN || temp->type == ROUT || temp->type == DROUT)
		{
			temp->type = -1;
			temp->next->type = -1;
		printf("temp->type: %d\n", temp->type);
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
		count = 0;
		while (temp2)
		{
			if (temp2->type == RIN || temp2->type == ROUT || temp2->type == DROUT)
				count++;
			if (temp2->type == PIPE)
			{
				ft_delete_redir(temp, count);
				temp = temp2;
				temp2 = temp2->next;
				break ;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return (0);
}
