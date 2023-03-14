#ifndef MINISHELL_H
# define MINISHELL_H

// ========== LIBRARY ========== //

# include "./libft/libft.h"
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

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

// extern	int	g_error;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmdexec
{
	char				**arg;
	char				*red;
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

/* clean.c */
void	ft_free_env(t_env **head);
void	ft_free_list(t_token **head);

/* [1.0] node_utils.c */

t_token	*create(char *str, int start, int end);
int		insert(t_token **head, char *str, int start, int end);
void	printstr(t_token *head);

/* [1.1] split_operators.c */

int		is_operator(char c);
int		skip_operator(int i, char c1, char c2);
t_token	*create_operator(char *str, int start, int end);
int		insert_op(t_token **head, char *str, int start, int end);
int		check_insert_op_and_init(t_token **head, char *cmd, int start, int i);

/* [1] first_split.c */

int		ft_get_state(char c, int state);
int		ft_first_split(char *cmd, t_token **head, int **s_i, int start);

/* [2.0] tokenizer.c */

void	assign_type_and_fd(t_token **token);
void	assign_type_and_lim(t_token **token);
int		assign_type(t_token **head);

/* [2]check_syntax_error.c */
void	display_error(t_token **token);

/* [2]check_syntax_error.c */

int		ft_check_syntax_error(t_token **token);

/* [3.0]expand_utils.c */

int	len_env(char *str, int i);
int	len_before_env(char *str, int i);
int	len_status(int status);
int	len_env_expanded(char *copyToken, int i, int len_env, t_env **env);
int	len_token_expanded(char *copyToken, t_env **env);

/* [3.1]expand_utils2.c */

int	is_allowed_char(char c);
int	write_env_value(int *len, t_env *env, char *copyToken, int i);

/* [3.2]expand.c */

int	expanded_var(char *copyToken, int i, int len_env, t_env **env, char *temp);

/* [3.3]expand_final_utils.c */

int	remove_first_quote(t_token *token, int i, int stateBefore);
int	count_removed_quotes(t_token *token);

/* [3]expand_final.c */

int	count_second_quote(t_token *token, int i, int state);
int	remove_second_quote(int state, int stateBefore);
char	*check_node(t_token *token, int i, int j, int state);
int	remove_quotes(t_token **token);
int	remove_quotes_in_node(t_token *token, int j, int state, int stateBefore);

/* env_parsing.c */

int	env_parser(char **envp, t_env **head, int i);
char	*token_expanded(char *temp, char *copyToken, t_env **env);
char	*fill_expand(char *copyToken, t_env **env);
int	call_expand(t_token *token, t_env **env);
int	expand(t_token **token, t_env **env);

// ========================================================================= //
//                               EXEC                                        //
// ========================================================================= //

/* BUILT-INS */

int		ft_cd(char **command);
int		ft_echo(char **str, int fd);
int		ft_env(t_env *head, int fd, char **envp);
int		ft_export(t_env **env, t_cmdexec **head, int i);
int		ft_pwd(int fd);
int		ft_unset(t_env **env, char **command, int i);

int		check_equal(char *str);
int		check_symbolerror(char c);

/*EXEC*/

char	*get_path(t_env **env, t_cmdexec **head, int i, char *path);
char	*check_access(char *exe, char *command, char *path);
void	shellcmd(t_cmdexec **head, char **envp, t_env **env);
void	ft_builtins(t_cmdexec **head, t_env **env, char **envp);

#endif