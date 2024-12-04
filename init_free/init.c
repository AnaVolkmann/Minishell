/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:56 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/04 15:22:35 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO - verifiar saidas de erro!
// CURRENT WORKING DIRECTORY

/** @brief Initializes the environment for the shell by duplicating
 *  and parsing the original environment.
 * 
 * This function duplicates the original environment variables,
 *  initializes `env->parsed_env`, and 
 * sets default variables. It returns 0 on success and 1 on error.
 
 * @param env The environment structure to initialize.
 * @param original_env The original environment variables passed
 *  to the program.
 * @return 0 on success, 1 on failure.*/
int	init_environment(t_env *env, char **original_env)
{
	if (!env)
		return ;
	env->parsed_env = init_dinam_env(original_env);
	if (!env->parsed_env)
	{
		//error;
	}
	
}

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
		return (NULL);
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

t_shell	*init_shell(t_shell *shell, char **original_env)
{
	shell->pid = getpid();
	shell->last_pid = 0;
	shell->exit_status = 0;
	shell->output_fd = STDOUT_FILENO;
	shell->input_fd = STDIN_FILENO;
	return (shell);
}

t_ast_node	*init_ast(t_ast_node *ast)
{
	ast->args = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}
