#include "./LIB/minishell.h"

int	g_error = 0;

void	ft_free(t_cmdexec **head, char *command)
{
	ft_free_cmdexec(head);
	free(command);
	// free(head);
}

int	parsing(t_token *head, t_cmdexec *cmd, t_env *env)
{
	int		i;
	int		state;
	char	*command;

	i = 0;
	state = ARG;
	head = NULL;
	cmd = NULL;
	command = NULL;
	command = readline("mimishell$> ");
	if (command == NULL)
		return (1);
	add_history(command);
	ft_first_split(command, &head, (int *[2]){&state, &i}, 0);
	ft_check_syntax_error(&head);
	expand(&head, &env);
	ft_count_redir(&head, 0);
	cmd_final(&cmd, &head);
	return (exec_main(&cmd, env, command));
}

int	exec_main(t_cmdexec **head, t_env *env, char *command)
{
	if (command == NULL)
		return (1);
	ft_exec(head, &env);
	if (*head != NULL)
		ft_free(head, command);
	return (0);
}

int	main(int ac, char **av, char **envp)
{	
	t_env	*env;

	(void)ac;
	(void)av;
	env = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (env_parser(envp, &env, 0, 0) == 1)
		return (ft_free_env(&env), 1);
	while (1)
	{
		if (parsing(NULL, NULL, env) == 1)
			exit(1);
	}
	if (env)
		ft_free_env(&env);
	rl_clear_history();
	return (0);
}
