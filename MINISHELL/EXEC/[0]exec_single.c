#include "../LIB/minishell.h"

// function to delete, just a test to fill out one node

void	fill_cmd_test(t_cmdexec **head)
{
	t_cmdexec	*temp;

	temp = malloc(sizeof(t_cmdexec));
	temp->arg = malloc(sizeof(char *) * 2);
	temp->arg[0] = ft_strdup("ls");
	temp->arg[1] = ft_strdup("-la");
	temp->lim = NULL;
	temp->fd_in = 0;
	temp->fd_out = 1;
	temp->next = NULL;
	if (!*head)
	{
		*head = temp;
		return ;
	}
}

// function to get the path or return the command if it's not found

char	*get_path(t_env **env, t_cmdexec **head, int i, char *path)
{
	t_env		*temp;
	t_cmdexec	*texec;
	char		*exe;
	char		**env_path;

	texec = *head;
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->name, "PATH", 4) == 0)
		{
			env_path = ft_split(temp->value, ':');
			while (temp->value[i])
			{
				path = ft_strjoin(env_path[i], "/");
				if (!path)
					return (NULL);
				exe = check_access(exe, texec->arg[0], path);
				i++;
			}
		}
		temp = temp->next;
	}
	return (texec->arg[0]);
}

char	*check_access(char *exe, char *command, char *path)
{
	char *copy;
	exe = ft_strjoin(path, command);
	if (!exe)
		return (NULL);
	if (access(exe, F_OK || X_OK) == -1)
		return (NULL);
	copy = ft_strdup(exe);
	return (free(exe), copy);
}

// execute the command from the path returned by get_path

void	shellcmd(t_cmdexec **head, char **envp, t_env **env)
{
	char		*path;
	
	path = get_path(env, head, 0, NULL);
	if (execve(path, (*head)->arg, envp) == -1)
		return ;
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;
	t_cmdexec	*head;
	int			i;
	(void)ac;
	(void)av;
	i = -1;

	env = NULL; // initialize environment list
	head = NULL; // initialize command list
	env_parser(envp, &env, i); // fill the environment list
	fill_cmd_test(&head); // fill the command list
	shellcmd(&head, envp, &env); // execute the command
	return (0);
}
