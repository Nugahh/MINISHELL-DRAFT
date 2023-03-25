#include "./LIB/minishell.h"

int g_error;

void	ft_free(t_cmdexec *cmd, char *command)
{
	ft_free_cmdexec(&cmd);
	free(command);
	free(cmd);
}
void	parsing(t_token *head, t_cmdexec *cmd, t_env *env, char **envp)
{
	int i;
	int	state;
	char *command;

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
	ft_count_redir(&head);
	printstr(head);
	cmd_final(&cmd, &head);
	printcmdexec(cmd);
	return (exec_main(cmd, env, envp, command));
}

void	exec_main(t_cmdexec *cmd, t_env *env, char **envp, char *command)
{
	ft_exec(cmd, &env, envp);
	ft_free(cmd, command);
}

int	main(int ac, char **av, char **envp)
{	
	(void)ac;
	(void)av;
	t_env *env;

	env = NULL;
	if (env_parser(envp, &env, 0, 0) == 1)
		return (ft_free_env(&env), 1);
	while (1)
		parsing(NULL, NULL, env, envp);
	ft_free_env(&env);
	return (0);
}

