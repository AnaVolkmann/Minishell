/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 15:22:16 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern int	g_signal;

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

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}			t_token;

typedef struct s_shell
{
	int		pid;
	int		last_pid;
	int		exit_status;
	int		output_fd;
	char	**path;
	char	**envp;
}				t_shell;

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					file_type;//indicates the type of redirection(input, output, append), if no redirec, set to 0.
}						t_ast_node;

/* typedef struct s_env
{
	char	**original_env;
	char	***parsed_env;
}		t_env; */

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

t_shell		*init_shell(t_shell *shell, char **original_env);
t_ast_node	*init_ast(t_ast_node *ast);
char		**init_dinam_env(char **original_env);

/*********************Parsing*********************/

t_ast_node	*parse_tokens(t_token **tokens);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_redirection(t_token **tokens);
t_ast_node	*parse_command(t_token **token);

/*********************Parsing Utils***************/

t_ast_node	*create_new_ast_node(t_token_type type);
t_ast_node	*create_file_node(t_token *token);
int			count_command_args(t_token *current);
t_ast_node	*create_and_link_redirection(t_token **tokens, t_token *tmp);

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
void		sighandler(int signal);
void		ft_signal(void);
void		remove_env(char **envp, int index);
void		update_exit(int i, t_shell *shell);

/*********************Free***********************/

void		free_envp(char **envp);
void		free_shell(t_shell *shell);
void		free_ast(t_ast_node **ast);

/********************Run Commands****************/

int			execute(char *cmd, char *const *argument, t_shell *shell);

#endif
