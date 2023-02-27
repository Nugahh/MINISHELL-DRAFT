#ifndef MINISHELL_H
# define MINISHELL_H

// ========== LIBRARY ========== //

# include "./libft/libft.h"
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

// ========== STRUCTURES ========== //

typedef enum TYPE
{
	ARG,
	FD,
	LIM,
	RIN,
	ROUT,
	DRIN,
	DROUT,
	PIPE
}	t_TYPE;

typedef enum STATE
{
	DEFAULT,
	SINGLE,
	DOUBLE
}	t_STATE;

// extern int	g_error;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmdexec
{
	t_token				**arg;
	t_token				*red;
	int					fd_in;
	int					fd_out;
	struct s_cmdexec	*next;
}	t_cmdexec;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

int		main(int ac, char **av, char **envp);

// ========================================================================= //
//                               PARSING                                     //
// ========================================================================= //

/* [1.0] node_utils.c */

t_token	*create(char *str, int start, int end);
void	insert(t_token **head, char *str, int start, int end);
void	printstr(t_token *head);

/* [1.1] split_operators.c */

int		is_operator(char c);
int		skip_operator(int i, char c1, char c2);
t_token	*create_operator(char *str, int start, int end);
void	insert_op(t_token **head, char *str, int start, int end);
int		check_insert_op_and_init(t_token **head, char *cmd, int start, int i);

/* [1] first_split.c */

int		ft_get_state(char c, int state);
int		ft_skip_spaces(char *cmd, int i);
int		ft_check_spaces_and_not_operator(char *cmd, int i);
int		insert_and_init_new_start(char *cmd, t_token **head, int i, int start);
void	ft_split_test(char *cmd, t_token **head, int i, int start);

/* [2.0] tokenizer.c */

void	assign_type_and_fd(t_token **token);
void	assign_type_and_lim(t_token **token);
void	assign_type(t_token **token);

/* [2]check_syntax_error.c */
void	display_error(t_token **token);

/* [2]check_syntax_error.c */

bool	ft_check_syntax_error(t_token **token);


/* env_parsing.c */

void	env_parser(char **envp, t_env **head, int i);

// ========================================================================= //
//                               EXPAND                                      //
// ========================================================================= //

void	ft_check_state_and_expand(t_token **head, t_env **env);
void	expand_default(t_token **head, t_env **env, int i, int state);
void	expand_single(t_token **head, int s, int i, char *copy);
void	expand_double(t_token **head, t_env **env, int s, int i);

/* UTILS */

void	deletenode(t_token **head, t_token *toDel);
void	eraser(int i, int len, char *str);
void	env_lookup(t_token **head, t_env **env, char *copy, t_token *temp);

// ========================================================================= //
//                               EXEC                                        //
// ========================================================================= //

/* BUILT-INS */

int	ft_echo(char **str, int fd);
int	ft_env(t_env *head, int fd, char **envp);
int	ft_pwd(int fd);

#endif