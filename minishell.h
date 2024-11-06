/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 18:00:42 by ana-lda-         ###   ########.fr       */
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
#include "./libft/libft.h"
#include <stdbool.h>
#include <limits.h>

typedef enum	e_token_type
{
	TOKEN_WORD,      // For comands and arguments
	TOKEN_PIPE,      // For '|'
	TOKEN_REDIR_IN,  // For '<'
	TOKEN_REDIR_OUT, // For '>'
	TOKEN_REDIR_APPEND, // For '>>'
	TOKEN_REDIR_HEREDOC, // For '<<'
	TOKEN_ENV_VAR, // For environment variables
	TOKEN_COMMAND,
	TOKEN_RULE,
	TOKEN_QUOTE,
}	t_token_type;

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

t_token	**tokenizer(char *line);

#endif
