/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/25 14:21:55 by alawrence        ###   ########.fr       */
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
/*# include <term.h>*/
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
	T_WORD,// For comands and arguments
	T_PIPE,// For '|'
	T_REDIR_IN,// For '<'
	T_REDIR_OUT,// For '>'
	T_REDIR_APPEND,// For '>>'
	T_REDIR_HEREDOC,// For '<<'
	T_ENV_VAR,// For environment variables
}				t_token_type;

/************************RULES*********************/

typedef struct s_pipe_state
{
	int					executed_pipes_index;
	int					current_input_fd;
	int					current_output_fd;
	int					input_files_count;
	int					output_files_count;
	int					pipes_count;
	int					has_input_file;
	int					has_output_file;
	int					is_redirection_or_pipe;
	int					heredoc_status;
	int					children_count;
	int					second_heredoc_status;
}				t_pipe_state;

/**************************envp*********************/

typedef struct s_env
{
	char				**original_env;
	char				**parsed_env;
	int					last_pid;
	int					exit_status;
	int					pid;
}					t_env;

/***********************TOKEN STRUCT*****************/

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}					t_token;

/*************************SHELL STRUCT******************/

/* typedef struct s_shell
{
	int					output_fd;
	int					input_fd;
}					t_shell; */

typedef struct s_ast_node
{
	t_token_type		type;
	//struct s_shell		*shell;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					file_type;
}					t_ast_node;

/******************Input processing***************/

t_token		*process_to_tokenize_input(char *input);
int			has_invalid_redirections(const char *input);
int			has_misplaced_operators(const char *input);
int			syntax_error_checker(const char *input);
int			has_logical_operators(const char *input);

/*******************Token Manegement**************/

void		free_tokens(t_token *tokens);
t_token		*tokenize_input(char *input);
t_token		*new_token(t_token_type type, char *value);
void		handle_word(char **input, t_token **tokens);
void		handle_special_chars(char **input, t_token **tokens);
void		add_token_to_list(t_token **tokens, t_token *new_token);

/********************Syntax Handling****************/

void		add_word_token(char **start, char **input, t_token **tokens);
void		update_quote_status(char c, int *in_quote, char *quote_char);
int			has_unclosed_quotes(const char *input);
void		update_quote_counts(char c, int *s_q_count, int *d_q_count);
const char	*skip_spaces(const char *input);
int			is_invalid_operator(const char **input);

/********************Environment Init***************/

char		**init_dinam_env(char **original_env);
int			init_environment(t_env *env, char **original_env);
t_ast_node	*init_ast(t_ast_node *ast);
void		is_sus_dir(char *path_, char *file, int *status);
int			specify_error(char *file, int _status);
int			get_shell_exit_status(int err);

/********************Parsing*************************/

t_ast_node	*parse_tokens(t_token **tokens);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_redirection(t_token **tokens);
t_ast_node	*parse_command(t_token **token);

/********************Parsing Utils*******************/

t_ast_node	*create_new_ast_node(t_token_type type);
t_ast_node	*create_file_node(t_token *token);
int			count_command_args(t_token *current);
t_ast_node	*build_redirection_node(t_token **tokens, t_token *tmp);
void		expand_vars_in_ast(t_ast_node *head, t_env *env);

/********************Builtin Commands****************/

int			bash_exit(char **args, int arg_count, t_env *env);
int			ft_cd(char *path, t_env *env);
int			ft_export(char *path, t_env *env);
int			ft_unset(char *name, t_env *env);
int			echo(char **args, int argc, int *fd, t_env *env);
int			ft_env(t_env *env);
char		*ft_pwd(t_env *env, int flag);

/********************Extras************************/

char		*expansion(char *path, t_env *env);
char		*new_env_var(char *name, char *value);
char		*get_env(char *var, char **envp);
char		**realloc_envp(char **envp, int size);
int			find_env(t_env *env, char *name);
int			count_envp(char **envp);
void		handle_ctrl_c(int a);
void		child_ctrl_c(int sig_num);
void		setup_signal_handlers(void);
void		remove_env(char **envp, int index);
void		update_exit(int i, t_env *env);
int			str_cmp(char *s_1, char *s_2, char *s_3);
int			check_line(char **input);
int			count_substrings(char *str, char del);
int			str_cmp(char *s_1, char *s_2, char *s_3);
char		*strcopy(char *src);
int			count_strings_in_array(char **array);
int			find_env_var_index(t_env *env, char *name);
void		s_strcopy(char *s1, char *s2, int start, int end);
int			is_string_numeric(char *s1);
char		*remove_quotes_from_str(char *str, int si_q_c, int do_q_c, int a);

/********************Free*************************/

void		free_envp(char **envp);
void		free_ast(t_ast_node **ast);
void		cleanup_and_exit_shell(t_env *env, int status);
void		free_parsed_env(t_env *env);
void		ft_exit(char **cmd, t_env *env);
int			string_to_int(char *str);

/*******************Shell Utilities****************/

void		run_minishell(t_env *env);
void		command_executer(t_ast_node *head, t_env *env, int *status);
int			execute_ast_node(t_ast_node *head, t_pipe_state *piped_state,
				t_env *env);
int			handle_redirection_cmd(t_ast_node *head, t_pipe_state *piped_state,
				t_env *env, int *fd);
int			handle_piped_cmd_exec(t_ast_node *head, t_pipe_state *piped_state,
				t_env *env, int *fd);
int			prepare_and_execute_cmd(char **cmd, int *fd, t_pipe_state *piped,
				t_env *env);
int			open_file_for_redirection(t_ast_node *head,
				t_pipe_state *pipe_state, t_env *env, int status);
char		**merge_cmd_args(char **f_args, char **cmd);
int			execute_basic_cmd(char **cmd, int *_fd, char **env,
				t_pipe_state *piped);
void		close_pipe_ends(int read_fd, int write_fd);
int			command_is_builtin(char *cmd);
char		*verify_path_without_env(char *file, int mode);
int			is_path_accessible(char *path, int mode);
char		**prepare_cmd_args(char *cmd, char **envp, int c);
char		*find_next_substring(char *str, char del, int *index);
int			sizeof_str(char *str, char end);
int			run_command_builtin(char **arguments, t_env *env, int *fd_out);
int			run_command_builtin_2(char **cmd_args, t_env *env, int *fd_out);
int			execute_cmd_with_redirect(char **cmd, int *fd, char **env,
				t_pipe_state *piped);
char		*get_file_path(char *file, char **envp, char *env_var, int mode);
void		child_fds_managment(t_pipe_state *piped, int *_fd, int *fd_);
void		parent_fds_managment(t_pipe_state *piped, int *_fd, int *fd_);
//int			check_safety(t_ast_node *head, char *path);

/********************Pipe and Redirect*********************/

void		adjust_ast_node_for_execution(t_ast_node *head);
int			check_file_permissions(t_ast_node *head, char **env);
void		count_redirect_and_pipes(t_ast_node *head,
				t_pipe_state *piped_state);
void		init_or_reset_pipe_state(t_pipe_state *pipe_state, int f);
int			handle_input_redirection(t_ast_node *head,
				t_pipe_state *pipe_state, t_env *env);
int			handle_output_redirection(t_ast_node *head,
				t_pipe_state *pipe_state);
int			wait_for_children(int status, t_pipe_state *piped);
int			find_substr_index(char **str, char *sub_str, int n);
char		*create_subpath_from_var(char *env_var, char *file,
				int env_var_len, int *flag);
int			switch_fds_identifier(t_pipe_state *state, int index, int con);


/*******************HeheDoc Handling******************/

void		quite_heredoc(int n);
int			have_quotes(char *s);
int			exec_here_doc(char *limiter, t_pipe_state *pipe_state, t_env *env);
void		read_and_write(t_pipe_state *pipe_state, char *limiter,
				t_env *env, int is_expandable);

/****************************FD**************************/

void		parent_fds_managment(t_pipe_state *piped, int *_fd, int *fd_);
void		child_fds_managment(t_pipe_state *piped, int *_fd, int *fd_);

/**************************expansion**********************/

int			simple_refactor(char **array, int index, char *str, int i);
int			count_special_chars(char *str, int s_q, int d_q);
int			count_whitespace_flaws(char *str, int a, int b, int res);
int			count_total_flaws(char **array);
void		expand_vars_in_ast(t_ast_node *head, t_env *env);
char		**refactor_args_array(char **args, int *sintax_fix);
char		*recursively_expand_vars(char *var, t_env *env, int control, int *array);
char 		*expand_vars_in_string(char *str, t_env *env, int start, int *expand_idx);
int			is_valid_var_start(char *str, int index, int control);
char		*replace_var_with_value(char *old_val, char *new_val, int start, int end);


/*********************************execution**********************/

int	manage_single_builtin_execution(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped);
int	exec_builtin_with_simple_pipe(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped);
int	exec_builtin_with_pipe(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped);
void	exec_builtin_and_exit(char **cmd_args, t_env *env, int *fd_out);
int	run_child_with_redirs(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped);
int	run_builtin_child(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped);
int	manage_builtin_execution(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped);

int			execute(char *cmd, char *const *argument, t_env *envp, int *fd);

#endif