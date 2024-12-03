/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:54:22 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/03 14:59:19 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Parses a single environment variable entry,
 * splitting it into a key-value pair.
 * 
 * searches for an '=' character in the entry string, then 
 * splits the string into a key
 * and a value, storing them in `env->parsed_env[index]`.
 * 
 * @param env The environment structure where parsed variables are stored.
 * @param entry The environment variable entry to parse (key=value).
 * @param index The index in `env->parsed_env` where the parsed 
 * key-value pair will be stored.
 * @return 1 on success, 0 on failure.*/
int	parse_env_entry(t_env *env, char *entry, int index)
{
	char	*equal_sign;
	int		key_len;
	//int		len;

	equal_sign = ft_strchr(entry, '=');
	if (!equal_sign)
		return (0);
	key_len = equal_sign - entry;
	//len = ft_strlen(equal_sign + 1);
	env->parsed_env[index] = malloc(sizeof(char *) * 2);
	if (!env->parsed_env)
		return (0);
	env->parsed_env[0] = ft_strndup(entry, key_len);
	env->parsed_env[1] = ft_strdup(equal_sign + 1);
	if (!env->parsed_env[index][0] || !env->parsed_env[index][1])
	{
		free(env->parsed_env[index][0]);
		free(env->parsed_env[index][1]);
		free(env->parsed_env[index]);
		return (0);
	}
	return (1);
}

/** @brief Counts the number of parsed environment variables
 * in `env->parsed_env`.
 * 
 * This function iterates over `env->parsed_env` and returns the total count
 *  of environment variables.
 * 
 * @param parsed_env The parsed environment variables array.
 * @return The number of environment variables in `parsed_env`.*/
int	count_parsed_env(char ***parsed_env)
{
	int	count;

	count = 0;
	while ((*parsed_env)[count])
		count++;
	return (count);
}

/** @brief Adds the "SHELL" variable with a default
 *  value ("minishell") to `env->parsed_env`.
 * 
 * This function allocates memory for the "SHELL" variable
 * entry and sets its value to "minishell".
 * @param env The environment structure where the new "SHELL" 
 * variable will be added.
 * @param count A pointer to the current index for adding new
 * entries in `env->parsed_env`.*/
void	add_shell_variable(t_env *env, int *count)
{
	env->parsed_env[*count] = malloc(2 * sizeof(char *));
	env->parsed_env[*count][0] = ft_strdup("SHELL");
	env->parsed_env[*count][1] = ft_strdup("minishell");
	(*count)++;
}

/** @brief Adds the "PWD" variable with the current working
 * directory to `env->parsed_env`.
 * 
 * This function allocates memory for the "PWD" variable entry
 *  and sets its value to the current working directory.
 *
 * @param env The environment structure where the new "PWD" variable
 *  will be added.
 * @param count A pointer to the current index for adding new 
 * entries in `env->parsed_env`.
 * @param cwd The current working directory to set as the value 
 * for the "PWD" variable.*/
void	add_pwd_variable(t_env *env, int *count, char *cwd)
{
	env->parsed_env[*count] = malloc(2 * sizeof(char *));
	env->parsed_env[*count][0] = ft_strdup("PWD");
	env->parsed_env[*count][1] = ft_strdup(cwd);
	(*count)++;
}
