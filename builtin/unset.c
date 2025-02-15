/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:08 by lufiguei          #+#    #+#             */
/*   Updated: 2024/12/04 16:35:13 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_error(char *name, t_env *env, int i);

/** @brief looks for the target inside the shell->envp, if it finds, calls
 * the remove function, returns error otherwise */
int	ft_unset(char *name, t_env *env)
{
	int	index;

	if (!name || !*name || !env->parsed_env)
		return (update_exit (1, env->shell), unset_error(name, env, 0), 1);
	index = find_env(env, name);
	if (index >= 0)
		return (update_exit (0, env->shell),
			remove_env(env->parsed_env, index), 0);
	return (update_exit (1, env->shell), unset_error(name, env, 1), 1);
}

static void	unset_error(char *name, t_env *env, int i)
{
	if (!name || !*name)
		ft_putstr_fd("Error: Invalid variable name\n", 2);
	if (!env->parsed_env)
		ft_putstr_fd("Error: Environment is not set\n", 2);
	if (i == 1)
	{
		ft_putstr_fd("Error: Variable not found: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("\n", 2);
	}
}
