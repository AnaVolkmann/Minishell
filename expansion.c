/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:44:25 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/03 13:56:58 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** @brief it needs to get the pointer right after to the $ in caller 
 *  the commented loop is usefull if we want to pass the whole word, like $HOME
 * instead of just HOME */
char	*expansion(char *path, t_shell *shell)
{
	char	*env_value;

	if (!path[0])
		return (NULL);
	if (ft_strcmp(path, "$") == 0)
		return (ft_itoa(shell->pid));
	if (ft_strcmp(path, "?") == 0)
		return (ft_itoa(shell->exit_status));
	if (ft_strcmp(path, "!") == 0)
		return (ft_itoa(shell->last_pid));
	//if (!in_double_quote)
	env_value = get_env(path, shell->envp);
	if (!env_value)
		return (NULL);
	return (ft_strdup(env_value));
}

//$?: Exit status of the last command
//$$: Current process ID.
//$!: PID of the last background job.
// do i need to handle VAR="Hello" and echo ${VAR}world to "Hello world"?
// also handle {}?