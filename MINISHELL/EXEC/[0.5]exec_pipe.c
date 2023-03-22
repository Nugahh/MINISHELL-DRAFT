#include "../LIB/minishell.h"

void	ft_redir_exec(t_cmdexec **head)
int	ft_pipe(t_cmdexec **head, t_env **env)
{
	char	**paths;
	int		status;
	t_cmdexec	*cmd;

	cmd = *head;
	paths = get_path_and_split(env);
	if (cmd && cmd->next == NULL)
		return (free_paths(paths), ft_single(head, paths));
	while (cmd)
	{
		if (cmd->next == NULL)
			ft_last(head, paths);
		else
			ft_child(head, paths);
		wait(&status);
		cmd = cmd->next;
	}
	free_paths(paths);
	return (0);
}
