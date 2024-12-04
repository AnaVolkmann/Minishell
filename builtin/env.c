/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:55:50 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/06 12:34:30 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief searching for an environment  variable in the provided
 *  environment array and returning its value.
 * This function takes the name of an environment 
 variable and an array of environment 
 * variables, and returns the value of the variable if found.
 * @param var   The name of the environment variable to search for.
 * @param envp  The array of environment variables (e.g., `environ`).
 * 
 * @return A string containing the value of the environment variable,
 *  or NULL if the variable is not found.*/
char	*get_env(char *var, char **envp)
{
	int	i;
	int	var_len;
	int	eq_pos;

	if (!var || !envp)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr_i(envp[i], '=');
		if (eq_pos != -1 && !ft_strncmp(envp[i], var, var_len)
			&& envp[i][var_len] == '=')
			return (ft_substr(envp[i], eq_pos
					+ 1, ft_strlen(envp[i]) - eq_pos - 1));
		i++;
	}
	return (NULL);
}

/** @brief function prints the whole envp */
int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env->shell || !env->parsed_env)
		return (update_exit(1, env->shell),
			ft_putstr_fd("Error: environment is not set or missing\n", 2), 1);
	while (env->parsed_env[i])
	{
		if (printf("%s\n", env->parsed_env[i]) < 0)
			return (update_exit(1, env->shell), perror("write"), 1);
		i++;
	}
	return (update_exit(0, env->shell), 0);
}
