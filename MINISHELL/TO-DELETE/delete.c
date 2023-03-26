#include "../LIB/minishell.h"

void	printstr(t_token *head)
{
	t_token	*temp;

	temp = head;
	if (head == NULL)
	{
		printf("liste vide\n");
		return ;
	}
	while (temp)
	{
		printf("node:");
		printf("%s | type: %d ", temp->value, temp->type);
		printf("\n");
		temp = temp->next;
	}
}

// int	write_status(int i, char *temp, char *copyToken)
// {
// 	char	*status;
// 	int		j;

// 	j = 0;
// 	status = ft_itoa(g_error);
// 	while (status[j])
// 		temp[i++] = status[j++];
// 	free(status);
// 	return (len_status(g_error));
// }

void	printcmdexec(t_cmdexec *head)
{
	t_cmdexec	*temp;
	int			i;	

	temp = head;
	if (head == NULL)
	{
		printf("liste vide\n");
		return ;
	}
	while (temp)
	{
		printf("command: ");
		i = 0;
		if (temp->arg[0])
		{	
			while(temp->arg[i])
			{
				printf("arg = %s | ", temp->arg[i]);
				i++;
			}
		}
		printf("lim = %s | ", temp->lim);
		printf("fd_in = %d | ", temp->fd_in);
		printf("fd_out = %d\n", temp->fd_out);
		temp = temp->next;
	}
}