/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:08 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/20 12:22:47 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_error(char *name, t_shell *shell, int i);

/** @brief looks for the target inside the shell->envp, if it finds, calls
 * the remove function, returns error otherwise */
int	ft_unset(char *name, t_shell *shell)
{
	int	index;

	if (!name || !*name || !shell->envp)
		return (update_exit (1, shell), unset_error(name, shell, 0), 1);
	index = find_env(shell->envp, name);
	if (index >= 0)
		return (update_exit (0, shell), remove_env(shell->envp, index), 0);
	return (update_exit (1, shell), unset_error(name, shell, 1), 1);
}

static void	unset_error(char *name, t_shell *shell, int i)
{
	if (!name || !*name)
		ft_putstr_fd("Error: Invalid variable name\n", 2);
	if (!shell->envp)
		ft_putstr_fd("Error: Environment is not set\n", 2);
	if (i == 1)
	{
		ft_putstr_fd("Error: Variable not found: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("\n", 2);
	}
}

//(TODO) {} ()
// >> append?
// << should be given a delimiter, then read the input until a line containing
// the delimiter is seen. However, it doesn’t have to update the history!

// Handle ’ (single quote) which should prevent the shell from interpreting
// the meta-characters in the quoted sequence

// Handle " (double quote) which should prevent the shell from interpreting
// the meta-characters in the quoted sequence except for $ (dollar sign).

// GCC use on Makefile?

// if inside quotes, dont expand, but run command if its exactly it.
// "ls" -l works "ls -l" no, neither "ls "-l or "ls"-l
// pwd | $oi | cat > test
// echo "$USER" = lufiguei
// echo '$USER' = $USER