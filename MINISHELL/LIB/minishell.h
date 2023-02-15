/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:40:48 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/15 18:42:48 by khuynh           ###   ########.fr       */
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

int	main(int ac, char **av, char **envp);

// ========== PARSING ========== //


// ========== EXEC ========== //

#endif