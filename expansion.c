/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:44:25 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/27 11:48:19 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** @brief handles edge cases and searches the env var inside the shell's envp
 * if it not finds it, returns an error
 * the function caller needs to free is return value */
char	*expansion(char *path, t_shell *shell)
{
	char	*env_value;

	if (!path || !path[0])
		return (update_exit(1, shell), NULL);
	if (ft_strcmp(&path[0], "'") == 0)
		return (update_exit(0, shell), path);
	if (ft_strcmp(path, "$$") == 0 && ft_strcmp(&path[1], "$") == 0)
		return (update_exit(0, shell), ft_itoa(shell->pid));
	if (ft_strcmp(path, "$?") == 0)
		return (update_exit(0, shell), ft_itoa(shell->exit_status));
	if (ft_strcmp(path, "$!") == 0)
		return (update_exit(0, shell), ft_itoa(shell->last_pid));
	env_value = get_env(path, shell->envp);
	if (!env_value)
		return (update_exit(1, shell), NULL);
	return (update_exit(0, shell), ft_strdup(env_value));
}

// do i assume it will always be formatted? or i assume i can have """""$USER"""""
//$?: Exit status of the last command
//$$: Current process ID.
//$!: PID of the last background job.
// do i need to handle VAR="Hello" and echo ${VAR}world to "Hello world"?
// also handle {}?