/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:20:27 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/08 13:16:55 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIB/minishell.h"

int	main(int ac, char **av)
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
