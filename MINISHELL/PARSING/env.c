/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:08:46 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/19 17:44:22 by khuynh           ###   ########.fr       */
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
		printf("%s\n", copy[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	extract_env(envp);
}

