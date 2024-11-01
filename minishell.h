/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:56:04 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/01 13:27:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stropts.h>
# include <sys/types>
# include <sys/stat>
# include <sys/wait>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history>
# include <readline/readline>

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

#endif
