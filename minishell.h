/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/05 17:52:21 by ana-lda-         ###   ########.fr       */
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
//# include <stropts.h>
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

extern char **environ;

typedef enum	e_token_type
{
	COMMAND,
	RULE,
	OPERATOR,
	QUOTE,
	ENV_VAR,
	WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char		*value;
	struct s_token	*next;
}	t_token;

t_token	**tokenizer(char *line);

#endif
