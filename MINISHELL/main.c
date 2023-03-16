#include "./LIB/minishell.h"

int g_error;

void	ft_free(t_cmdexec *cmd, char *command)
{
	ft_free_cmdexec(&cmd);
	free(command);
	free(cmd);
}
void	parsing(t_token *head, t_cmdexec *cmd, char **envp)
{
	int i;
	t_env *env;
	int	state;
	char *command;

	env = NULL;
	if (env_parser(envp, &env, 0) == 1)
		return (ft_free_env(&env));
	while (1)
	{
		i = 0;
		state = ARG;
		g_error = 0;
		head = NULL;
		cmd = NULL;
		command = readline("minishell$> ");
		add_history(command);
		ft_first_split(command, &head, (int *[2]){&state, &i}, 0);
		ft_check_syntax_error(&head);
		expand(&head, &env);
		remove_quotes(&head);
		cmd_final(&cmd, &head);
		printcmdexec(cmd);
		ft_free(cmd, command);
	}
}


int	main(int ac, char **av, char **envp)
{	

	(void)ac;
	(void)av;
	t_token		*head;
	t_cmdexec	*cmd;

	head = NULL;
	cmd = NULL;
	parsing(head, cmd, envp);
}

