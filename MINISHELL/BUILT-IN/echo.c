/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:50:54 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/19 15:33:04 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIB/minishell.h"

int check_flag(char **str)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 0;
	i = 0;
	while (str[i] && ft_strlen(str[i]) >= 2)
	{
		if(str[i][j] == '-' && str[i][j + 1] == 'n')
		{
			j++;
			while (str[i][j] == 'n')
				j++;
			if (j == ft_strlen(str[i]))
				count++;
		}
		else
			return (count);
		i++;
		j = 0;
	}
	return (count);
}

int	ft_echo(char **str)
{
	int	i;
	int	n;

	str++;
	n = 0;
	i = check_flag(str);
	if (i > 0)
		n++;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1] && str[i][0] != '\0')
			printf(" ");
		i++;
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