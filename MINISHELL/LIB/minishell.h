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
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>

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

extern	int	g_error;

typedef struct s_token
{
	char			*value;
	int				type;
	// struct stat		*stat;
	struct s_token	*next;
}	t_token;

typedef struct s_cmdexec
{
	char				**arg;
	char				*lim;
	int					fd_in;
	int					fd_out;
	int					fd_pipe[2];
	struct s_cmdexec	*next;
}	t_cmdexec;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

int	main(int ac, char **av, char **envp);

// ========================================================================= //
//                               PARSING                                     //
// ========================================================================= //

void	parsing(t_token *head, t_cmdexec *cmd, t_env *env, char **envp);

/* clean.c */

void    deletenode(t_token **head, t_token *toDel);
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
int		ft_check_syntax_error(t_token **token);

/* [3.0]expand_utils.c */

int		len_env(char *str, int **i_j);
int		len_before_env(char *str, int i);
int		len_status(int status);
int		len_env_expanded(char *copyToken, int **i_j, int len_env, t_env **env);
int		len_token_expanded(char *copyToken, t_env **env);

/* [3.1]expand_utils2.c */

int		is_allowed_char(char c);
int		write_env_value(int *len, t_env *env, char *copyToken, int i);

/* [3.2]expand.c */

int		expanded_var(char *copyToken, int **i_j, t_env **env, char *temp);

/* [3.3]expand_final_utils.c */

int		remove_first_quote(int stateBefore, int state);
int		remove_second_quote(int state, int stateBefore);
int		c_rq(t_token *token, int stateBefore);

/* [3]expand_final.c */

char	*check_node(t_token *token, int i, int j, int state);
int		remove_quotes(t_token **token);
int		remove_quotes_in_node(int state, int stateBefore);
char	*fill_expand(char *copyToken, t_env **env);
int		call_expand(t_token *token, t_env **env);
int		expand(t_token **token, t_env **env);

/* [4]fill_command.c */

size_t	token_argcount(t_token **head);
t_cmdexec *create_nodecmd(t_token **head, size_t i, t_cmdexec *new);
int		insert_nodecmd(t_cmdexec **head, t_token **token);
void	fill_redir(t_cmdexec *tofill, t_token *src);
void	printcmdexec(t_cmdexec *head);
void	cmd_final(t_cmdexec **head, t_token **token);
void	ft_free_cmdexec(t_cmdexec **head);

int	ft_count_redir(t_token **token);

/* [4.1]open_fd.c */

int	rin_file(t_cmdexec *head, t_token *src);
int	rout_file(t_cmdexec *head, t_token *src);

/*[bis]env_parsing.c*/

int	env_parser(char **envp, t_env **head, int i, int j);

// ========================================================================= //
//                               EXEC                                        //
// ========================================================================= //

void	exec_main(t_cmdexec *cmd, t_env *env, char **envp, char *command);

/* BUILT-INS */

int		ft_cd(char **command);
int		ft_echo(char **str, int fd);
int		ft_env(t_env **head, int fd, char **envp);
void	ft_exit(t_cmdexec *head, t_env *env);
int		ft_export(t_env **env, t_cmdexec **head, int i);
int		ft_pwd(int fd);
int		ft_unset(t_env **env, char **command, int i);

int		check_equal(char *str);
int		check_symbolerror(char c);
void	all_clean(t_cmdexec **head, t_env *env);
int		open_temp();

/*EXEC*/

/* [0.1]exec_utils.c */

void	free_paths(char **paths);

/* [0.2]heredoc.c */

int	heredoc(t_cmdexec **head);

/* [0.3]find_cmd.c */

char	**get_path_and_split(t_env **env);
char	*check_cmd(char *cmd, char **paths);

/* [0.4]exec_child.c */

void	ft_single(t_cmdexec *cmd, t_env **env, char **paths, char **envp);
void	ft_first(t_cmdexec *cmd, char **paths, char **envp);
void	ft_last(t_cmdexec *cmd, char **paths, int fd_pipe[2], char **envp);
void	ft_between_pipes(t_cmdexec *cmd, char **paths, int fd_pipe[2], char **envp);
void	ft_child(t_cmdexec *cmd, char **paths, int fd_pipe[2], char **envp);

/* [0.5]exec_pipe.c */

void	ft_fork(t_cmdexec *head, t_env **env, char **paths, char **envp);
int		ft_exec(t_cmdexec *head, t_env **env, char **envp);

char	*get_path(t_env **env, t_cmdexec **head, int i, char *path);
char	*check_access(char *exe, char *command, char *path);
void	shellcmd(t_cmdexec **head, char **envp, t_env **env);
void	ft_builtins(t_cmdexec **head, t_cmdexec *cmd, t_env **env, char **envp);
int		ft_is_builtins(t_cmdexec *cmd);


#endif