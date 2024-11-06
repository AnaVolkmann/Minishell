/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:51:33 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell shell;
	
	//check_input(argc, argv);
	//init_shell(&shell, envp);
	input = readline("Prompt > ");
	//if (signal received)
	//	call sighandler;
	tokenizer(input);
	// call parser
	// call exec
	free(input);
	rl_clear_history();
	return (0);
}