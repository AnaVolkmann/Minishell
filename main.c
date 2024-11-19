/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/07 12:44:40 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **original_env)
{
	char	*input;
	t_token	*tokens;
	t_shell	shell;
	//t_env	env;//estrutura para lidarcom env trimmed e inteira

	(void)argv;
	if (argc != 1)
		return (printf("Error: Too many Arguments, try \'./minishell\'\n"), 1);
	rl_catch_signals = 0;
	ft_signal();
	init_shell(&shell, original_env);
	//env = malloc(sizeof(env));
	//if (argc == 1 && init_shell(&shell, env, original_env))
	//{
		//shell_execution_loop
		//cheanup and exit function
	//}
	input = readline("Prompt > ");
	if (input == NULL)
		return (free_shell(&shell), printf("exit\n"), 0);
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		shell.input = input;
	}
	//check_input(argc, argv);
	tokens = process_to_tokenize_input(input);
	// call parser
	// call execute;
	rl_clear_history();
	free_tokens(tokens);
	free_shell(&shell);
	return (0);
}
