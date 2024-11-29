/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:56 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/29 15:02:27 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO - verifiar saidas de erro!

/** @brief Initializes the parsed environment by processing
 * all entries in the original environment.
 * 
 * counts the entries in `original_env`, allocates memory for
 * `env->parsed_env`, and processes each entry using `parse_env_entry`.
 
 * @param env The environment structure to store parsed variables.
 * @param original_env The original environment variables passed
 * to the program.
 * @return 1 on success, 0 on failure.*/
int	init_parse_env(t_env *env, char **original_env)
{
	int		count;
	int		i;
	char	*equal_sign;

	i = 0;
	count = 0;
	while (original_env[count])
		count++;
	env->parsed_env = malloc(sizeof(char **) * (count + 1));
	if (!env->parsed_env)
		return (0);
	while (i < count)
	{
		if (!parse_env_entry(env, original_env[i], i))
		{
			free_envp(env->parsed_env);
			return (0);
		}
		i++;
	}
	env->parsed_env[i] = NULL;
	return (1);
}

// CURRENT WORKING DIRECTORY
/**
 * @brief Initializes default environment
 * variables such as "SHELL" and "PWD".
 * 
 * checks if the "SHELL" and "PWD" variables are present in 
 * `env->parsed_env`. If not, it adds them with default values
 * ("minishell" for "SHELL" and the current directory for "PWD").

 * @param env The environment structure where default variables
 * are checked and added.*/
void	init_default_variables(t_env *env)
{
	char	cwd[1024];
	int		shell_found;
	int		pwd_found;
	int		i;

	i = 0;
	pwd_found = 0;
	shell_found = 0;
	getcwd(cwd, sizeof(cwd));
	while (env->parsed_env[i])
	{
		if (ft_strcmp(env->parsed_env[i][0], "SHELL") == 0)
		{
			free(env->parsed_env[i][1]);
			env->parsed_env[i][1] = ft_strdup("minishell");
			shell_found = 1;
		}
		if (ft_strcmp(env->parsed_env[i][0], "PWD") == 0)
		{
			free(env->parsed_env[i][1]);
			env->parsed_env[i][1] = ft_strdup(cwd);
			pwd_found = 1;
		}
		i++;
	}
	add_missing_default_variables(env, shell_found, pwd_found, cwd);
}

/** @brief Adds missing default variables ("SHELL" and "PWD")
 *  to `env->parsed_env` if they are not present.
 * 
 * This function checks if "SHELL" and "PWD" are found in
 *  `env->parsed_env`. If not, it adds them with 
 * default values. It reallocates `env->parsed_env` to accommodate 
 * any new variables.
 
 * @param env The environment structure where missing variables will be added.
 * @param shell_found A flag indicating whether "SHELL" is already 
 * present in `env->parsed_env`.
 * @param pwd_found A flag indicating whether "PWD" is already
 *  present in `env->parsed_env`.
 * @param cwd The current working directory to use for the "PWD"
 *  variable.*/
void	add_missing_default_variables(t_env *env,
				int shell_found, int pwd_found, char *cwd)
{
	int		count;
	int		i;
	char	***new_parsed_env;

	i = 0;
	count = count_parsed_env(env);
	new_parsed_env = malloc(sizeof(char **) * (count + 3)); // Space for 2 new vars and NULL terminator
	if (!new_parsed_env)
		return (NULL);
	while (i < count)
	{
		new_parsed_env[i] = env->parsed_env[i];
		i++;
	}
	if (!shell_found)
		add_shell_variable(env, &count);
	if (!pwd_found)
		add_pwd_variable(env, &count, cwd);
	new_parsed_env[count] = NULL;
	free(env->parsed_env);
	env->parsed_env = new_parsed_env;
}

/** @brief Duplicates the environment variables from `env` to a
 *  new memory block.
 * 
 * This function copies all environment variables from `env`
 *  into a newly allocated array of strings. 
 * It returns a pointer to the new environment array or NULL on
 *  failure.
 
 * @param env The original environment variables to duplicate.
 * @return A new array of environment variables, or NULL on failure.*/
char	**duplicate_env_variables(char **env)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	i = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i)
			{
				return (free(new_env[i]), free(new_env), NULL);
			}
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

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
	if (!env || !original_env)
	{
		write(2, "Error: Invalid arguments to init_environment.\n", 46);
		return (1);
	}
	env->original_env = duplicate_env_variables(original_env);
	if (!env->original_env)
	{
		write(2, "Error: Failed to duplicate environment variables.\n", 50);
		return (1);
	}
	if (init_parsed_env(env, original_env))
	{
		write(2, "Error: Failed to parse environment variables.\n", 46);
		return (1);
	}
	init_default_variables(env);
	return (0);
}

/* t_shell	*init_shell(t_shell *shell, char **original_env)
{
	shell->pid = getpid();
	shell->path = NULL;
	shell->envp = init_dinam_env(original_env);
	return (shell);
}

t_ast_node	*init_ast(t_ast_node *ast)
{
	ast->args = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
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
} */
