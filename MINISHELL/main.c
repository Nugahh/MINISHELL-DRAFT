/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:20:27 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/15 18:43:37 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIB/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

void	init_structoken(t_token *tok)
{
	tok->value = malloc(sizeof(char));
	tok->type = START;
	tok->next = NULL;
}

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

