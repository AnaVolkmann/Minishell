/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/29 16:22:36 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_FILE 10
# define READ_FROM_APPEND 20
# define WRITE_FILE 30
# define WRITE_FILE_APPEND 40
# define EXECUTE_FILE 50
# define FILE_READY 60

/*******************INCLUDES****************/

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./libft/libft.h"
# include <stdbool.h>
# include <limits.h>

/*****************GLOBAL VARIABLE*****************/

extern int	g_signal;

/********************TOKEN TYPE*******************/

typedef enum e_token_type
{
	TOKEN_WORD,// For comands and arguments
	TOKEN_PIPE,// For '|'
	TOKEN_REDIR_IN,// For '<'
	TOKEN_REDIR_OUT,// For '>'
	TOKEN_REDIR_APPEND,// For '>>'
	TOKEN_REDIR_HEREDOC,// For '<<'
	TOKEN_ENV_VAR,// For environment variables
}				t_token_type;

/************************RULES*********************/

typedef struct	s_pipe_state
{
	int					executed_pipes_index;
	int					input_files_count;
	int					output_files_count;
	int					pipes_count;
	int					current_input_fd;
	int					current_output_fd;
	int					has_input_file;
	int					has_output_file;
	int					is_redirection_or_pipe;
	int					heredoc_status;
	int					children_count;
	int					second_heredoc_status;
}				t_pipe_state;

/**************************envp*********************/

typedef struct		s_env
{
	char				**original_env;
	char				***parsed_env;
}					t_env;

/***********************TOKEN STRUCT*****************/

typedef struct		s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}					t_token;

/*************************SHELL STRUCT******************/

typedef struct		s_shell
{
	int					pid;
	int					last_pid;
	int					exit_status;
	int					output_fd;
	int					input_fd;
	char				**path;
	char				**envp;
}					t_shell;

typedef struct		s_ast_node
{
	t_token_type		type;
	struct s_shell		*shell;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					file_type;//indicates the type of redirection(input, output, append), if no redirec, set to 0.
}					t_ast_node;


/******************Input processing****************/

t_token		*process_to_tokenize_input(char *input);
int			has_invalid_redirections(const char *input);
int			has_misplaced_operators(const char *input);
int			syntax_error_checker(const char *input);
int			has_logical_operators(const char *input);

/******************Token Manegement****************/

void		free_tokens(t_token *tokens);
t_token		*tokenize_input(char *input);
t_token		*new_token(t_token_type type, char *value);
void		handle_word(char **input, t_token **tokens);
void		handle_special_chars(char **input, t_token **tokens);
void		add_token_to_list(t_token **tokens, t_token *new_token);

/**********************Syntax**********************/

void		add_word_token(char **start, char **input, t_token **tokens);
void		update_quote_status(char c, int *in_quote, char *quote_char);
int			syntax_error_checker(const char *input);
int			has_unclosed_quotes(const char *input);

/*******************Syntax_Utils************************/

void		update_quote_counts(char c, int *s_q_count, int *d_q_count);
const char	*skip_spaces(const char *input);
int			is_invalid_operator(const char **input);

/*********************Init***********************/

int			init_parse_env(t_env *env, char **original_env);
void		init_default_variables(t_env *env);
void		add_missing_default_variables(t_env *env,
				int shell_found, int pwd_found, char *cwd);
char		**duplicate_env_variables(char **env);
int			init_environment(t_env *env, char **original_env);
void		add_pwd_variable(t_env *env, int *count, char *cwd);
void		add_shell_variable(t_env *env, int *count);
int			count_parsed_env(char ***parsed_env);
int			parse_env_entry(t_env *env, char *entry, int index);

/*********************Parsing*********************/

t_ast_node	*parse_tokens(t_token **tokens);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_redirection(t_token **tokens);
t_ast_node	*parse_command(t_token **token);

/*********************Parsing Utils***************/

t_ast_node	*create_new_ast_node(t_token_type type);
t_ast_node	*create_file_node(t_token *token);
int			count_command_args(t_token *current);
t_ast_node	*build_redirection_node(t_token **tokens, t_token *tmp);

/**********************Builtins********************/

int			bash_exit(char **args, int arg_count, t_shell *shell);
int			ft_cd(char *path, t_shell *shell);
int			ft_export(char *path, t_shell *shell);
int			ft_unset(char *name, t_shell *shell);
int			echo(char **args, int argc, int fd, t_shell *shell);
int			ft_env(t_shell *shell);
char		*ft_pwd(t_shell *shell, int flag);

/********************Extras***********************/

char		*expansion(char *path, t_shell *shell);
char		*new_env_var(char *name, char *value);
char		*get_env(char *var, char **envp);
char		**realloc_envp(char **envp, int size);
int			find_env(char **envp, char *name);
int			count_envp(char **envp);
//void		sighandler(int signal);
//void		ft_signal(void);
void		handle_ctrl_c(int a);
void		child_ctrl_c(int sig_num);
void		setup_signal_handlers(void);
void		remove_env(char **envp, int index);
void		update_exit(int i, t_shell *shell);
int			str_cmp(char *s_1, char *s_2, char *s_3);
int			check_line(char **input);

/*********************Free***********************/

void		free_envp(void **envp);
void		free_shell(t_shell *shell);
void		free_ast(t_ast_node **ast);
void		cleanup_and_exit_shell(t_env *env, int status);

/********************Run Commands****************/

void		run_minishell(t_env *env);
void		command_executer(t_ast_node *head, t_env *env, int *status);
int			execute_ast_node(t_ast_node *head, t_pipe_state *piped_state, t_env *env);
int			handle_redirection_cmd(t_ast_node *head, t_pipe_state *piped_state, t_env *env, int *fd);
int			handle_piped_cmd_exec(t_ast_node *head, t_pipe_state *piped_state, t_env *env, int *fd);

/********************RUN UTILS******************/

void		adjust_ast_node_for_execution(t_ast_node *head);
int			check_file_permissions(t_ast_node *head, char **env);
void		count_redirect_and_pipes(t_ast_node *head, t_pipe_state *piped_state);
void		init_or_reset_pipe_state(t_pipe_state *pipe_state, int f);
int			handle_input_redirection(t_ast_node *head, t_pipe_state *pipe_state, t_env *env);
int			handle_output_redirection(t_ast_node *head, t_pipe_state *pipe_state);
int			wait_for_children(int status, t_pipe_state *piped);

/*******************HANDLE_HEREDOC******************/

void		quite_heredoc(int n);
int			have_quotes(char *s);
int			exec_here_doc(char *limiter, t_pipe_state *pipe_state, t_env *env);
void		read_and_write(t_pipe_state *pipe_state, char *limiter, t_env *env, int is_expandable);

#endif
