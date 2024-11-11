/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/08 15:48:23 by ana-lda-         ###   ########.fr       */
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
/* 	TOKEN_COMMAND,
	TOKEN_RULE,
	TOKEN_QUOTE, */ //comentei pq nao estou utilizando de momento!

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}			t_token;

typedef struct s_shell
{
	int		pid;
	char	**path;
	char	**envp;
	char	*input;
}				t_shell;

typedef struct s_env
{
	char	**orinal_env;
	char	***parsed_env;
}		t_env;

/******************input processing****************/

t_token	*process_to_tokenize_input(char *input);

/******************TOKEN MANAGEMENT****************/

void	free_tokens(t_token *tokens);
t_token	*tokenize_input(char *input);
t_token	*new_token(t_token_type type, char *value);
void	handle_word(char **input, t_token **tokens);
void	handle_special_chars(char **input, t_token **tokens);
void	add_token_to_list(t_token **tokens, t_token *new_token);

/**********************syntax**********************/

void	add_word_token(char **start, char **input, t_token **tokens);
void	update_quote_status(char c, int *in_quote, char *quote_char);
int		syntax_error_checker(const char *input);
int		has_unclosed_quotes(const char *input);

/**********************Builtins********************/

int		bash_exit(char **args, int arg_count);
int		ft_cd(char *path, t_shell *shell);
int		ft_export(char *path, t_shell *shell);
char	*ft_pwd(void);
int		ft_setenv(char *name, char *value, t_shell *shell, int overwrite);
int		ft_unset(char *name, t_shell *shell);
int		echo(char **args, int argc, int fd);
char	*get_env(char *var, char **envp);

/********************Extras***********************/

char	*expansion(char *path);
char	*new_env_var(char *name, char *value);
char	**realloc_envp(char **envp, int size);
int		find_env(char **envp, char *name);
int 	count_envp(char **envp);
void	sighandler(int signal);
void	remove_env(char **envp, int index);

/*********************Init***********************/

t_shell	*init_shell(t_shell *shell, char **original_env);
char	**init_dinam_env(char **original_env);

/********************Run Commands****************/

//int		run_command_builtin(char *cmd, char *path);

#endif
