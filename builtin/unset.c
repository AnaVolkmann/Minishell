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

//(TODO) print error? shell exit status? falta exit e export
// check quotes {} (), test builtins
// check all builtins
// check error messages
// check exit status

// GCC use on Makefile?
// if inside quotes, dont expand, but run command if its exactly it.
// "ls" -l works "ls -l" no, neither "ls " -l or "ls"-l
// pwd | $oi | cat > test