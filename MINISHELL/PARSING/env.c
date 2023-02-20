/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:08:46 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/20 23:44:01 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

int	nb_env(char **envp)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (envp[i++])
		count++;
	return (count);
}

char **extract_env(char **envp)
{
	int		count;
	int		i;
	char	**copy;

	i = 0;
	count = nb_env(envp);
	copy = malloc(sizeof(char *) * count);
	if (!copy)
		return (0);
	while (envp[i])	
	{
		copy[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(copy[i], envp[i], ft_strlen(envp[i]) + 1);
//		printf("%s\n", copy[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_env *create_env(char *name, char *value)
{
	t_env	*new;
	
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (0);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	return (new);
}

void	insert_env(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*temp;

	new = create_env(name, value);
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	env_parser(char **envp, t_env **head)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	t_env	*env;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				name = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				break;
			}
			j++;
		}
		insert_env(head, name, value);
		free(name);
		free(value);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	extract_env(envp);
}
