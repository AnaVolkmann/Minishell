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
	char *input;
	(void)argv;
	t_env	env;//estrutura para lidarcom env trimmed e inteira

	signal(SIGINT, sighandler); // handles ctrl c
	signal(SIGQUIT, SIG_IGN); //this is maybe useless, since ctrl \ should do nothing
	env = malloc(sizeof(env));
	if (argc == 1 && init_shell(env, original_env));
	{
	    //shell_execution_loop
	    //cheanup and exit function
	}
	return (0);
	/*while (1)
	{
		input = readline("Prompt > ");
		if (input == NULL) // handles ctrl d?
			break ;
		if (ft_strlen(input) > 0)
			add_history(input);
	}
	check_input(argc, argv);
	init_shell(&shell, envp);
	process_to_tokenize_input(input);
	 call parser
	 call exec
	free(input);
	rl_clear_history();
	return (0);*/
}

int	run_command_builtin(char *cmd, char *path)
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
}
// this needs testing