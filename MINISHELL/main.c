/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:20:27 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/13 16:03:53 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIB/minishell.h"

void	init_structoken(t_token *tok)
{
	tok->value = NULL;
	tok->type = START;
	tok->next = NULL;
}

void	init_structcmd(t_cmdexec *exec);

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*command;

	while (1)
	{
		command = readline("minishell$> ");
		add_history(command);
	}
}

