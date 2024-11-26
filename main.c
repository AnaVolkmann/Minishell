/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/20 16:45:10 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minishell(t_shell *shell, t_ast_node **ast);

int	g_signal = 0;

int	main(int argc, char **argv, char **original_env)
{
	t_shell		shell;
	t_ast_node	*ast;

	(void)argv;
	if (argc != 1)
		return (printf("Error: Too many Arguments, try \'./minishell\'\n"), 1);
	rl_catch_signals = 0;
	ft_signal();
	init_shell(&shell, original_env);
	init_ast(ast);
	while (1)
	{
		if (minishell(&shell, &ast) != 0)
			break ;
		if (g_signal == 2)
		{
			g_signal = 0;
			update_exit(130, &shell);
			continue ;
		}
	}
	return (rl_clear_history(), free_shell(&shell), free_ast(&ast), 0);
}

static int	minishell(t_shell *shell, t_ast_node **ast)
{
	t_token	*tokens;
	char	*input;

	input = readline("Minishell: ");
	if (input == NULL)
		return (printf("exit\n"), 0);
	if (ft_strlen(input) > 0)
		add_history(input);
	if (syntax_error_checker(input) == 1)
		return (free(input), update_exit(2, shell), 2); // sair do programa ou devolver o prompt?
	tokens = process_to_tokenize_input(input);
	if (tokens != NULL)
	{
		*ast = parse_tokens(&tokens);
		free(tokens);
	}
	// execute ast
	return (0);
}

/*const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[7];

 	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "TOKEN_ENV_VAR";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}
void	display_tokens(t_token *tokens)
{
	t_token	*token;
	token = tokens;
    
	while (token)
	{
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
			token->value, get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		token = token->next;
	}
}
void print_ast(t_ast_node *node)
{
    if (!node)
        return;

    // Print current node type
    printf("AST Node Type: %s\n", get_token_type_name(node->type));

    // If it's a command node, print its arguments
    if (node->type == TOKEN_WORD && node->args)
    {
        printf("Arguments: ");
        int i = 0;
        while (node->args[i])
        {
            printf("%s ", node->args[i]);
            i++;
        }
        printf("\n");
    }

    // If it's a redirection or pipe, print its left and right children
    if (node->left)
    {
        printf("Left Child:\n");
        print_ast(node->left);  // Recursively print left child
    }
    if (node->right)
    {
        printf("Right Child:\n");
        print_ast(node->right);  // Recursively print right child
    }
}

int main(int argc, char **argv, char **original_env)
{
    char        *input;
    t_token     *tokens;
    t_shell     shell;
    t_ast_node  *ast;

    (void)argv;

    // Argument check
    if (argc != 1)
        return (printf("Error: Too many Arguments, try './minishell'\n"), 1);

    // Signal handling setup
    rl_catch_signals = 0;
    ft_signal();

    // Initialize shell environment
    init_shell(&shell, original_env);

    // Reading user input
    input = readline("Prompt > ");
    if (input == NULL)
        return (free_shell(&shell), printf("exit\n"), 0);

    if (ft_strlen(input) > 0)
    {
        add_history(input);  // Add input to history
        shell.input = input; // Store input in the shell structure
    }

    // Tokenize the input
    tokens = process_to_tokenize_input(input);

    // Display tokens to debug
    printf("Tokens:\n");
    display_tokens(tokens);  // Print the tokens to check if they are correct

    // Parse tokens into AST
    ast = parse_tokens(&tokens);

    // Print the AST for debugging
    if (ast) {
        printf("\nAST Structure:\n");
        print_ast(ast);  // This function prints the structure of the AST
    } else {
        printf("\nParsing failed.\n");
    }

    // call execution here
    // command_executer(ast, env);

    // Cleanup
    rl_clear_history();
    free_tokens(tokens);  // Free the token list
    free_shell(&shell);   // Free the shell structure

    return 0;
}*/
