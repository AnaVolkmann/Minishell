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

int	ft_unset(char *name, t_shell *shell)
{
	int	index;

	if (!name || !*name || !shell->envp)
		return (1);
	index = find_env(shell->envp, name);
	if (index >= 0)
		return (remove_env(shell->envp, index), 0);
	return (1);
}

//(TODO) print error? shell exit status?
// check quotes {} (), test builtins
// check all builtins
// check error messages
// check exit status

// GCC use on Makefile?
// if inside quotes, dont expand, but run command if its exactly it.
// "ls" -l works "ls -l" no, neither "ls " -l or "ls"-l
// pwd | $oi | cat > test