/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:50:54 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/19 00:55:29 by khuynh           ###   ########.fr       */
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
			if (ft_strncmp(str[i], "-n", ft_strlen(str[i])) == 0)
				n = 1;
			i++;
		}
		if (n == 1)
			i = 2;
		else
			i = 1;
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1] && str[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (n == 0)
		printf("\n");
	return (0);
}

int main (int ac, char **av)
{
	(void)ac;
	ft_echo(av);
}