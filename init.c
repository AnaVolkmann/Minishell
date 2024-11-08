/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:56 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/07 12:44:40 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell shell, char **env, char **original_env)
{
	(void)env;
	(void)original_env;
	(void)shell;
	shell.pid = getpid();
	shell.path = NULL;
	shell.envp = NULL;
	shell.input = NULL;
}

