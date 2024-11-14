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

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;

	t_shell shell;
	char	*home;

	shell.envp = init_dinam_env(envp);
	if (!shell.envp)
		return (1);
	home = expansion("HOME", &shell);
	printf("%s\n", home);
	free_envp(shell.envp);
	free(home);

	return (0);
}

/*int	main(int argc, char **argv, char **original_env)
{
	char	*input;
	t_token	*tokens;
	//t_shell	shell;
	//t_env	env;//estrutura para lidarcom env trimmed e inteira

	(void)original_env;
	(void)argv;
	if (argc != 1)
		return (printf("Error: Too many Arguments, try \'./minishell\'\n"), 1);
	rl_catch_signals = 0;
	ft_signal();
	//shell.envp = init_dinam_env(original_env);
	//env = malloc(sizeof(env));
	//if (argc == 1 && init_shell(&shell, env, original_env))
	//{
		//shell_execution_loop
		//cheanup and exit function
	//}
	input = readline("Prompt > ");
	if (input == NULL)
		return (printf("exit\n"), 0);
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		//shell.input = input;
	}
	//check_input(argc, argv);
	tokens = process_to_tokenize_input(input);
	// call parser
	// call exec
	rl_clear_history();
	free_tokens(tokens);
	//free_shell(&shell);
	return (0);
}*/

/*int	run_command_builtin(char *cmd, char *path)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(path), 0);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (echo(char **args, int argc, int fd), 0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (get_env(char *var, char **envp), 0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (bash_exit(char **args, int arg_count), 0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(char *path, char **envp), 0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(char *path, char **envp), 0);
}
int	run_command_exec(char *cmd, char *argument, char **envp)
{
	if (execve(cmd, argument, envp) == -1)
		return (printf("execve: %s: %s\n", cmd, strerror(errno)), 1);
	return (0);
}*/
