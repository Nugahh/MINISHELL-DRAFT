#include "./LIB/minishell.h"



void	ft_free(t_cmdexec **head, char *command)
{
	ft_free_cmdexec(head);
	free(command);
	// free(head);
}

void	parsing(t_token *head, t_cmdexec *cmd, t_env *env)
{
	int		i;
	int		state;
	char	*command;

	i = 0;
	state = ARG;
	// g_error = 0;
	head = NULL;
	cmd = NULL;
	command = readline("minishell$> ");
	add_history(command);
	ft_first_split(command, &head, (int *[2]){&state, &i}, 0);
	ft_check_syntax_error(&head);
	expand(&head, &env);
	ft_count_redir(&head, 0);
	printstr(head);
	cmd_final(&cmd, &head);
	printcmdexec(cmd);
	return (exec_main(&cmd, env, command));
}

void	exec_main(t_cmdexec **head, t_env *env, char *command)
{
	ft_exec(head, &env);
	ft_free(head, command);
}

int	main(int ac, char **av, char **envp)
{	
	t_env	*env;

	(void)ac;
	(void)av;
	env = NULL;
	if (env_parser(envp, &env, 0, 0) == 1)
		return (ft_free_env(&env), 1);
	while (1)
		parsing(NULL, NULL, env);
	ft_free_env(&env);
	return (0);
}
