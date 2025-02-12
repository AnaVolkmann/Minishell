/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/12 20:29:14 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO-DO CHECAR AONDE SERIA POSSIVEL UTILIZAR EXIT_STATUS DA ESTRUTURA AO INVEZ DE CRIAR UM INT NOVO EM CADA FUNCAOOOO
// TODO - CHECK_LINE
// execute_with_redirect;
// FINISH FUNCTION chech_file_permission

 /*      TO DO'S      */
// testar heredoc
// testar  multiplos redirects criam uma arvore AST com hierarquia errada
// testar expansão
// verificar saidas de erro
// verificar se frases de erro estao todas no stderr
// norminette
// fazer comentários

/*       Duvidas      */
// echo nao escreve com redirect
// exit still reachable ( provavelmente readline )
// checar pwd unset

int	g_signal = 0;

int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;

	(void)argv;
	setup_signal_handlers();
	env = malloc(sizeof(t_env));
	if (!isatty(1) || !isatty(0))
		return (free(env), 0);
	if (argc == 1 && init_environment(env, original_env))
	{
		run_minishell(env);
		cleanup_and_exit_shell(env, 0);
	}
	return (0);
}

/** @brief Main loop to run the minishell.
 *
 * This function runs the interactive shell, repeatedly prompting
 * the user for input with a `> ` prompt.
 * It processes the input by checking if the input is empty or a
 * newline, tokenizes the input,
 * parses it into an abstract syntax tree (AST), and then executes
 *  the corresponding commands.
 * The function will continue to loop until the user exits
 * (e.g., by entering `exit` or providing no input).
 *
 * @param env The environment structure containing environment
 * 								variables and shell state.*/
void	run_minishell(t_env *env)
{
	char		*input;
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
			break ;
		if (check_line(&input))
			continue ;
		add_history(input);
		tokens = process_to_tokenize_input(input);
		if (!tokens)
			env->shell->exit_status = 258;
		if (!env->shell->exit_status)
		{
			ast = parse_tokens(&tokens);
			/* if (ast->left == NULL && ast->right == NULL)
				execute(ast->args[0], ast->args, env); */
			command_executer(ast, env, &env->shell->exit_status);
			free_ast(&ast);
		}
		/* update_env_status? */
	}
}