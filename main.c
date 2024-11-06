/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 15:01:23 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *rl;
	t_shell shell;
	
	//check_input(argc, argv);
	//init_shell(&shell, envp);
	rl = readline("Prompt > ");
	//if (signal received)
	//	call sighandler;
	tokenizer(rl);
	// call parser
	// call exec
	free(rl);
	rl_clear_history();
	return (0);
}