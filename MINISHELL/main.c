#include "./LIB/minishell.h"

int g_error;

void	print_env(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		printf("%s=", temp->name);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	char	*command;
	t_token	*head;
	t_cmdexec	*cmd;
	t_env	*env;
	int i;

	int state;
	(void)ac;
	(void)av;
	(void)envp;
	i = 0;
	env = NULL;
	if (env_parser(envp, &env, i) == 1)
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
		remove_quotes(&head);
		printstr(head);
		insert_nodecmd(cmd, head);
		printcmdexec(cmd);
		ft_free_cmdexec(&cmd);
		free(cmd);
		ft_free_list(&head);
		free(command);
	}
}

