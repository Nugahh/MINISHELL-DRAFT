#include "../LIB/minishell.h"

int	ft_check_infile(t_token *token)
{
	int	fd;

	stat(token->next->value, token->next->stat);
	if (S_ISDIR(token->next->stat->st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	fd = open(token->next->value, O_RDONLY);
	if (fd == -1)
	{
		// fonction free
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_check_outfile(t_token *token)
{
	int	fd;

	stat(token->next->value, token->next->stat);
	if (S_ISDIR(token->next->stat->st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(token);
		free(token->next);
		return (1);
	}
	fd = open(token->next->value, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		// fonction free
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_check_redir(t_token **token)
{
	t_token *temp;

	temp = *token;
	while (temp)
	{
		if (temp->type == RIN)
		{
			if (ft_check_infile(temp) == 1)
				return (1);
		}
		else if (temp->type == ROUT || temp->type == DROUT)
			if (ft_check_outfile(temp) == 1)
				return (1);
		temp = temp->next;
	}
	return (0);
}