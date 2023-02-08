/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:40:48 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/07 21:20:04 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ========== LIBRARY ========== //

# include "libft/libft.h"
# include <stdio.h> 

// ========== STRUCTURES ========== //

enum type
{
	ARG,
	FD,
	LIM,
	RIN,
	ROUT,
	DRIN,
	DROUT,
	PIPE,
	DEFAULT,
	SINGLE,
	DOUBLE
}

typedef struct s_token
{
	char *value;
	int type;
	t_token *next;
}	t_token;

typedef struct s_cmdexec
{
	t_token 	*ARG;
	t_token		*RED;
	int			fd_in;
	int			fd_out;
	t_cmdexec	*next;
}	t_cmdexec;

