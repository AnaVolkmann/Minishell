/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:56 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/04 16:31:49 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Initializes the environment by duplicating the 
 * original environment and setting default variables.
 * 
 * This function initializes the `parsed_env` field of the `env` structure and
 * sets the `SHELL` and `?` environment variables to default values. Returns 1 on success,
 * 0 on failure.
 * 
 * @param env The environment structure to initialize.
 * @param original_env The original environment variables passed to the program.
 * @return 1 on success, 0 on failure.*/
int init_environment(t_env *env, char **original_env)
{
	if (!env)
		return (0);
	env->shell = malloc(sizeof(t_shell));
	if (!env->shell)
		return (0);
	init_shell(env->shell);
	env->parsed_env = init_dinam_env(original_env);
	if (ft_export("SHELL=minishell", env) != 0)
	{
		free(env->shell);
		//perror?
		free(env->parsed_env);
		return (0);
	}
	if (ft_export("?=0", env) != 0)
	{
		//perror?
		free(env->shell);
		free(env->parsed_env);
		return (0);
	}
	return (1);
}

/** @brief Duplicates the original environment into a new dynamically allocated array.
 * 
 * This function allocates memory for a new environment array, copies each environment 
 * variable from the original array into the new array, and returns the new environment.
 * 
 * @param original_env The original environment array.
 * @return A new dynamically allocated environment array, or NULL on failure.*/
char	**init_dinam_env(char **original_env)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (original_env[j])
		j++;
	new_envp = malloc(sizeof(char *) * (j + 1));
	if (!new_envp)
	{
		perror("Failed to allocate memory for environment array");
		return (NULL);
	}
	while (original_env[i])
	{
		new_envp[i] = ft_strdup(original_env[i]);
		if (!new_envp[i])
			return (free_envp(new_envp), NULL);
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

/** @brief Initializes the shell structure with default values.
 * 
 * This function sets the initial values for the `pid`, `last_pid`, `exit_status`, 
 * `output_fd`, and `input_fd` fields in the shell structure.
 * 
 * @param shell The shell structure to initialize.
 * @param original_env The original environment (not used in this function).
 * @return The initialized shell structure.*/
t_shell	*init_shell(t_shell *shell)
{
	shell->pid = getpid();
	shell->last_pid = 0;
	shell->exit_status = 0;
	shell->output_fd = STDOUT_FILENO;
	shell->input_fd = STDIN_FILENO;
	return (shell);
}

/** @brief Initializes an AST node with default values.
 * 
 * This function initializes the arguments, left, and right fields of an AST node to NULL.
 * 
 * @param ast The AST node to initialize.
 * @return The initialized AST node.*/
t_ast_node	*init_ast(t_ast_node *ast)
{
	ast->args = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}
