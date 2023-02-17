/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:40:48 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/17 15:31:00 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ========== LIBRARY ========== //

# include "libft/libft.h"
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>

// ========== STRUCTURES ========== //

typedef enum
{
	START,
	ARG,
	FD,
	LIM,
	RIN,
	ROUT,
	DRIN,
	DROUT,
	PIPE
} TYPE;

typedef enum
{
	DEFAULT,
	SINGLE,
	DOUBLE
} STATE;

typedef struct s_token		t_token;
typedef struct s_cmdexec	t_cmdexec;


struct	s_token
{
	char	*value;
	int		type;
	t_token	*next;
}	;

struct	s_cmdexec
{
	t_token		*arg;
	t_token		*red;
	int			fd_in;
	int			fd_out;
	t_cmdexec	*next;
}	;

// ========== BASE ========== //


// ========== PARSING ========== //


// ========== EXEC ========== //

#endif