#include "./LIB/minishell.h"

int	g_error;

int	main(int ac, char **av, char **envp)
{
	char	*command;
	t_token	*head;
	t_cmdexec	*cmd;
	t_env	*env;
	int state;
	int i;

	(void)ac;
	(void)av;
	(void)envp;
	env = NULL;
	if (env_parser(envp, &env, 0, 0) == 1)
		return (ft_free_env(&env), 1);
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
		ft_count_redir(&head, 0);
		// printstr(head);
		cmd_final(&cmd, &head);
		printcmdexec(cmd);
		ft_exec(&cmd, &env);
		ft_free_cmdexec(&cmd);
		free(cmd);
		free(command);
	}
}
