/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:40:48 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/08 22:06:42 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ========== LIBRARY ========== //

# include "libft/libft.h"
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>

// ========== STRUCTURES ========== //

enum e_type
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
} ;

enum e_status
{
	DEFAULT,
	SINGLE,
	DOUBLE
} ;

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

int		main(int ac, char **av);
void	init_structoken(t_token *tok);
void	init_structcmd(t_cmdexec *exec);

// ========== PARSING ========== //

// ========== EXEC ========== //

#endif