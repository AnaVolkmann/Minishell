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

	signal(SIGINT, sighandler); // handles ctrl c
	signal(SIGQUIT, SIG_IGN); //this is maybe useless, since ctrl \ should do nothing
	while (1)
	{
		input = readline("Prompt > ");
		if (input == NULL) // handles ctrl d?
			break ;
		if (ft_strlen(input) > 0)
			add_history(input);
	}
	//check_input(argc, argv);
	//init_shell(&shell, envp);
	tokenizer(input);
	// call parser
	// call exec
	free(input);
	rl_clear_history();
	return (0);
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

int	run_command_exec(char *cmd)
{
	// find what cmd and look it up on path;
}
