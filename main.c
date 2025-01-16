/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/12/04 17:21:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO - CHECK_LINE
// execute_with_redirect;
// expand_vars_in_ast
// FINISH FUNCTION chech_file_permission
// TODO - recursively_expand_variables
// TODO - verifiar saidas de erro!
// comentei funcoes em: path utils, handle_heredoc e execution_manager para compilar ***

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

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("Token type: %d, Value: %s\n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print indentation
void print_indentation(int level) {
    for (int i = 0; i < level; i++) {
        printf("    "); // 4 spaces for each level
    }
}

// Function to print the AST
void print_ast_visual(t_ast_node *node, int level) {
    if (!node) {
        print_indentation(level);
        printf("NULL\n");
        return;
    }

    // Print the current node type
    print_indentation(level);
    switch (node->type) {
        case TOKEN_PIPE:
            printf("+-- [Pipe]\n");
            break;
        case TOKEN_REDIR_IN:
            printf("+-- [Redirection: <]\n");
            break;
        case TOKEN_REDIR_OUT:
            printf("+-- [Redirection: >]\n");
            break;
        case TOKEN_REDIR_APPEND:
            printf("+-- [Redirection: >>]\n");
            break;
        case TOKEN_REDIR_HEREDOC:
            printf("+-- [Redirection: <<]\n");
            break;
        case TOKEN_WORD:
            printf("+-- [Command");
            if (node->args && node->args[0]) {
                printf(": %s", node->args[0]);
                for (int i = 1; node->args[i]; i++) {
                    printf(", %s", node->args[i]);
                }
            }
            printf("]\n");
            break;
        default:
            printf("+-- [Unknown Type: %d]\n", node->type);
    }

    // Recursively print the left and right children
    print_indentation(level);
    printf("  Left ->\n");
    print_ast_visual(node->left, level + 1);

    print_indentation(level);
    printf("  Right ->\n");
    print_ast_visual(node->right, level + 1);
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
	(void)env;
	//int			status;
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		//status = 0; // vou tentar sem esse status
		input = readline("Minishell: ");
		if (!input)
			break ;
		if (check_line(&input))
			continue ;
		add_history(input);
		tokens = process_to_tokenize_input(input);
		if (!tokens)
			return ; // retornei um erro qualquer
			//status = ast->shell->exit_status; // aqui o shell status ainda é 0, pois nao executou nada
		// if (tokens)
		// {
			print_tokens(tokens);
			ast = parse_tokens(&tokens);
			print_ast_visual(ast, 0);
		// 	while (ast) { // fiz um loop pra continuar executando a arvore
		// 		//command_executer(ast, env, &env->shell->exit_status);
		// 		execute(ast->args[0], ast->args, env); //funciona pra testar 1 comando por vez
		// 		ast = ast->right; // walk the tree?
		// 	}
		// 	free(ast);
		// }
		//ast->shell->exit_status = status;
		//update_env_status
	}
}
