/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsett.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:08 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:07:17 by lufiguei         ###   ########.fr       */
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
// study tokenizer and syntax checker

// GCC use on Makefile?
//if inside quotes, dont expand, but run command if its exactly it.
//"ls" -l works "ls -l" no, neither "ls " -l or "ls"-l

/*int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;

	t_shell shell;
	char	*home;

	shell.envp = init_dinam_env(envp);
	if (!shell.envp)
		return (1);
	home = expansion("HOME", &shell);
	printf("%s\n", home);
	free_envp(shell.envp);
	free(home);

	return (0);
}*/