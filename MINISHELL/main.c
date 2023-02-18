/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:20:27 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/18 20:14:48 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./LIB/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char	*command;
	t_token	*head;

	head = NULL;
	while (1)
	{
		command = readline("minishell$> ");
		printf("command = %s\n", command);
		add_history(command);
		ft_split_test(command, &head);
		free(command);
		printstr(head);
	}
}

