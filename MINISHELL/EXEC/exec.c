#include "../LIB/libft/libft.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmdexec
{
	char				**arg;
	char				*red;
	int					fd_in;
	int					fd_out;
	struct s_cmdexec	*next;
}	t_cmdexec;

t_env	*create_env(char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	return (new);
}

int	insert_env(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*temp;

	new = create_env(name, value);
	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	env_parser(char **envp, t_env **head, int i)
{
	int		j;
	bool	equal;
	char	*name;
	char	*value;

	while (envp[++i])
	{
		j = -1;
		equal = false;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=' && equal == false)
			{
				equal = true;
				name = ft_substr(envp[i], 0, j);
				if (!name)
					return (free(name), 1);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
			}
		}
		if (insert_env(head, name, value) == 1)
			return (1);
		free(name);
		free(value);
	}
	return (0);
}

void	fill_cmd_test(t_cmdexec **head)
{
	t_cmdexec	*temp;

	temp = malloc(sizeof(t_cmdexec));
	temp->arg = malloc(sizeof(char *) * 2);
	temp->arg[0] = ft_strdup("ls");
	temp->arg[1] = ft_strdup("-la");
	temp->red = NULL;
	temp->fd_in = 0;
	temp->fd_out = 1;
	temp->next = NULL;
	if (!*head)
	{
		*head = temp;
		return ;
	}
}

/*void	printexeclist(t_cmdexec **head)
{
	t_cmdexec	*temp;

	temp = *head;
	while (temp)
	{
		printf("arg: %s\n", temp->arg[0]);
		temp = temp->next;
	}
}*/

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
			while(temp->value[i])
			{
				path = ft_strjoin(env_path[i], "/");
				if (!path)
					return (NULL);
				exe = ft_strjoin(path, texec->arg[0]);
				if (!exe)
					return (NULL);
				if (access(exe, F_OK | X_OK) == 0)
					return (exe);
				free(exe);
				i++;
			}
		}
		temp = temp->next;
	}
	return (texec->arg[0]);
}

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
	printexeclist(&head); // print the command list
	shellcmd(&head, envp, &env); // execute the command
	return (0);
}
