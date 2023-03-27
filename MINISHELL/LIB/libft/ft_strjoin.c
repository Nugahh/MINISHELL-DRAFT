/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:38:24 by khuynh            #+#    #+#             */
/*   Updated: 2023/03/27 18:12:46 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*joiny;

	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		s1[0] = '\0';
	}
	joiny = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!joiny)
		return (0);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			joiny[i] = s1[i];
	while (s2[j])
		joiny[i++] = s2[j++];
	joiny[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	//free(s1);
	return (joiny);
}

/*
#include <stdio.h>

int	main(void)
{
	const char a[] = "hello";
	const char b[] = " world";
	printf("%s\n",  ft_strjoin(a, b));
}
*/