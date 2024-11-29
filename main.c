/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/29 16:29:58 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//The isatty() function shall test whether fildes,
//an open file descriptor, is associated with a terminal device
int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;

	(void)argv;
	setup_signal_handlers();
	env = malloc(sizeof(t_env));
	if (!isatty(1) || !isatty(0))
		return (free(env), 0);
	if(argc == 1 && init_environment(env, original_env))
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
 * @param env The environment structure containing environment variables and shell state.*/
void	run_minishell(t_env *env)
{
	char		*input;
	int			status;
	t_token		*tokens;
	t_ast_node	*ast;
	t_shell		*shell;

	/* shell.pid = getpid();  // Inicializa o PID do shell
    shell.last_pid = 0;    // Inicializa o PID do último comando
    shell.exit_status = 0; // Inicializa o status de saída como sucesso
    shell.output_fd = STDOUT_FILENO;  // Saída padrão (terminal)
    shell.input_fd = STDIN_FILENO;    // Entrada padrão (terminal)
    shell.path = env->parsed_env;  // Usando os caminhos de binários do parsed_env
    shell.envp = env->original_env;  */
	while (1)
	{
		status = 0;
		input = readline("Minishell: ");;
		if (!input)
			break;
		if (check_line(&input))
			continue;
		add_history(input);
		tokens = process_to_tokenize_input(input);
		if (!tokens)
			//status = exit_status
		if (!status)
		{
			ast = parse_tokens(&tokens);
			command_executer(ast, env, &status);
			free(ast);
		}
		//shell->exit_status = status;
		//update_env_status
	}
}

/* static int	minishell(t_shell *shell, t_ast_node **ast);

int	g_signal = 0;

int	main(int argc, char **argv, char **original_env)
{
	t_shell		shell;
	t_ast_node	*ast;

	(void)argv;
	if (argc != 1)
		return (printf("Error: Too many Arguments, try \'./minishell\'\n"), 1);
	rl_catch_signals = 0;
	//ft_signal();
	setup_signal_handlers();
	init_shell(&shell, oshell.pid = getpid();  // Inicializa o PID do shell
    shell.last_pid = 0;    // Inicializa o PID do último comando
    shell.exit_status = 0; // Inicializa o status de saída como sucesso
    shell.output_fd = STDOUT_FILENO;  // Saída padrão (terminal)
    shell.input_fd = STDIN_FILENO;    // Entrada padrão (terminal)
    shell.path = env->parsed_env;  // Usando os caminhos de binários do parsed_env
    shell.envp = env->original_env; riginal_env);
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
	//int		status;

	//status = 0;
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
	//funcai qye vai correr a arvere
	//vai receber ast
	//command_executer(ast, env, &status);
	return (0);
} */


/* 
funcao_que_corre_a_arvore_para_ver_o_tipo_do_node_e_depois_executar(ast)
{
	ver o tipo do node

	se ast->tipo == redirect
		//chamar funcao de redirect_geral(ast)
	se ast->tipo == exec
		//chamar funcao de execucao_cmd(ast)
	se ast->tipo == PIPE
		//chamar funcao de pipe
}

funcao_redirect_geral
		// se for (< RED_IN)
			//funcao de redir in
		// se for (> RED_OUT)
			//funcao de redir out
		// se for (>> HEREDOC)
			//funcao de exec HEREDOC
		// se for (>> RED_APPE)
			//funcao de redirect append

		// se nao ast->proximo = ast->next = NULL;
		//se o proximo appontar para algo
			//funcao_exec(ast->proximo)
}


funcao de pipe(exec)
{
	//forkar 2 vezes
	//um fork vai ser para a execucao do lado esquerdo
		//funcao_que_corre_a_arvore_para_ver_o_tipo_do_node_e_depois_executar(ast->erquerdo)
		//exit(flag_pra_recuperar_a_saida)
	//um fork vai ser para a execucao do lado direito
		//funcao_que_corre_a_arvore_para_ver_o_tipo_do_node_e_depois_executar(ast->direito)
		//exit(flag_pra_recuperar_a_saida)

	//recuperar saida do ultimo comando executado e guardar na estrutura
	//fim.
}



execucao_cmd(ast)
{
	//coisas da execucao
	//achar caminho
	//execve
	//bla bla bla
	//msg de erro
}
 */