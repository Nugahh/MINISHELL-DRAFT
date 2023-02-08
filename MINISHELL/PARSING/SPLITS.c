/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPLITS.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:22:51 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/08 14:48:30 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

char **first_split(char *command, int status, t_token tok)
{
	int	i;

	i = 0;
	while (command[i] != '\"' || command[i] != '\'')
	{
		status = DEFAULT;
		if (command[i + 1] == '\"')
		{
			return()
		}
		
}