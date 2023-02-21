#ifndef MINISHELL_H
# define MINISHELL_H

// ========== LIBRARY ========== //

# include "./libft/libft.h"
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
typedef	struct s_env		t_env;

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
	t_env		*env;
	t_cmdexec	*next;
}	;

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
}	;

int		main(int ac, char **av, char **envp);

// ========================================================================= //
//                               PARSING                                     //
// ========================================================================= //

/* [1.0] node_utils.c */

t_token *create(char *str, int start, int end);
void	insert(t_token **head, char *str, int start, int end);
//void	printstr(t_token *head);

/* [1.1] split_operators.c */

int		is_operator(char c);
int		skip_operator(int i, char c1, char c2);
t_token *create_operator(char *str, int start, int end);
void	insert_op(t_token **head, char *str, int start, int end);
int		check_insert_op_and_init(t_token **head, char *cmd, int start, int i);

/* [1] first_split.c */

int		ft_get_state(char c, int state);
int		ft_skip_spaces(char *cmd, int i);
int		ft_check_spaces_and_not_operator(char *cmd, int i);
int		insert_and_init_new_start(char *cmd, t_token **head, int i, int start);
void	ft_split_test(char *cmd, t_token **head, int i, int start);

// ========================================================================= //
//                               EXEC                                        //
// ========================================================================= //

#endif