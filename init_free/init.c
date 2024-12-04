/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:56 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/04 14:13:53 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO - verifiar saidas de erro!
// CURRENT WORKING DIRECTORY
// string_to_int(atoi);
// find_env_var_index;
// replace_env_var
// set_new_pwd

/**
 * @brief Initializes default environment
 * variables such as "SHELL" and "PWD".
 * 
 * checks if the "SHELL" and "PWD" variables are present in 
 * `env->parsed_env`. If not, it adds them with default values
 * ("minishell" for "SHELL" and the current directory for "PWD").

 * @param env The environment structure where default variables
 * are checked and added.*/
void	init_default_variables(t_env *env, int i)
{
	char	*new_pwd;

	i = find_env_var_index(env, "SHELL");
	if (i >= 0)
		remove_env_entry(env, i);
	ft_export("SHELL=minishell", env);
	ft_export("?=0", env);
	i = find_env_var_index(env, "PWD");
	new_pwd = get_current_dir(100, 5, 2);
	if (new_pwd)
	{
		if (i >= 0)
			remove_env_entry(new_pwd, env, i);
		//set_new_pwd_to_env(new_pwd, env, i); conferir set_pwd
		free(new_pwd);
	}
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
	new_env = malloc(sizeof(char **) * (count + 1));
	if (!new_env)
		return (NULL);
	while (i < count)
	{
		new_env[i] = strcopy(env[i]);
		i++;
	}
	new_env[count] = 0;
	return (new_env);
}

int	init_shell_structure(t_env *env, char **original_env, int i)
{
	int	a;
	int	b;

	env->original_env = duplicate_env_variables(original_env);
	while(original_env[i])
		i++;
	env->parsed_env = malloc(sizeof(char ***) * (i + 1));
	if (!env->parsed_env)
		return (0);
	a = -1;
	while(++a < i)
	{
		b = sizeof_str(original_env[b], '=');
		env->parsed_env[a] = malloc(sizeof(char **) * 2);
		env->parsed_env[a][0] = malloc(b * sizeof(char *));
		env->parsed_env[a][1] = malloc(
				(sizeof_str(original_env[a], '\0') - a) * sizeof(char *));
		if (!env->parsed_env[a] || !env->parsed_env[b][0]
			|| !env->parsed_env[a][1])
			return (0);
		ft_strcopy(env->parsed_env[a][0], original_env[a], 0, b);
		ft_strcopy(env->parsed_env[a][1], original_env[a],
			b + 1, sizeof_str(original_env[a], '\0'));
	}
	return (env->parsed_env[a] = 0, 1);
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
	int	index;
	int	i;
	int	status;

	index = 0;
	if (!env)
		return (0);
	status = init_shell_structure(env, original_env, 0);
	i = find_env_var_index(env, "SHLVL");
	if (i >= 0)
		index = string_to_int(env->parsed_env[i][1]);
//	update_exit(0, env->shell);
	init_default_variables(env, 0);
	return (status);
}

/* t_shell	*init_shell(t_shell *shell, char **original_env)
{
	shell.pid = getpid();
	shell.last_pid = 0;
	shell.exit_status = 0;
	shell.output_fd = STDOUT_FILENO;
	shell.input_fd = STDIN_FILENO;
	shell.path = env->parsed_env;s
	shell.envp = env->original_env;
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
