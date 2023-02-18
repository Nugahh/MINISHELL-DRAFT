/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:50:54 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/19 00:21:06 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

int argc_count(char **str)
{
	int	count;
	
	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	ft_echo(char **str)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (argc_count(str) > 1)
	{
		while (str[i])
		{
			if (ft_strcmp(str[i], "- n") == 0)
				n = 1;
			i++;
		}
		i = 0;
		while (str[i])
		{
			printf("%s", str);
			if (str[i + 1] && str[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (n == 0)
		printf("\n");
	return (0);
}

int main ()
{
	char str[] = "echo mdr";
	ft_echo(str);
}