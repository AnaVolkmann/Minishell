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
	// call exec
	rl_clear_history();
	free_tokens(tokens);
	free_shell(&shell);
	return (0);
}

/*int	run_command_builtin(char *cmd, char *path, t_shell *shell)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(path, &shell), 0);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (echo(char **args, int argc, int fd), 0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (get_env(path, shell->envp), 0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (bash_exit(char **args, int arg_count), 0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(path, shell->envp), 0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(), 0); //need to protect this
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(path, shell->envp), 0);
}
int	run_command_exec(char *cmd, char *const *argument, char **envp)
{
	char	*cmd_path;

	cmd_path = get_path(cmd);
	if (!cmd_path)
		return (printf("Command not found: %s\n", cmd), 1);
	if (execve(cmd_path, argument, envp) == -1)
		return (free(cmd_path), printf("execve: %s: %s\n", cmd, strerror(errno)), 1);
	return (0); //how to free if proccess executes?
}

static char	*get_path(char *cmd, char **envp)
{
	char	*cmd_path;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	cmd_path = get_env("PATH", envp);
	if (!cmd_path)
		return (NULL);
	//need to run through path and look for the correct path for cmd;
}*/

