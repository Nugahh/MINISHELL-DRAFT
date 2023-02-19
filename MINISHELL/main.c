/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:20:27 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/19 17:51:37 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./LIB/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*command;
	t_token	*head;

	(void)ac;
	(void)av;
	(void)envp;
	head = NULL;
	while (1)
	{
		command = readline("minishell$> ");
		printf("command = %s\n", command);
		add_history(command);
		ft_split_test(command, &head, 0, 0);
		free(command);
		printstr(head);
		free(head);
	}
}
