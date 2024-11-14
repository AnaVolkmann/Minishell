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

/** @brief sets or updates the environment variable
 * updates if variable exists and overwrite is 1
 * otherwise the variable is appended to the array */
int	ft_setenv(char *name, char *value, t_shell *shell, int overwrite)
{
	int		index;
	char	*new_var;

	if (!name || !value || !shell || !shell->envp)
		return (1);
	new_var = new_env_var(name, value);
	if (!new_var)
		return (1);
	index = find_env(shell->envp, name);
	if (index >= 0)
	{
		if (overwrite == 1)
		{
			free(shell->envp[index]);
			shell->envp[index] = new_var;
		}
		else
			free (new_var);
		return (0);
	}
	shell->envp = realloc_envp(shell->envp, count_envp(shell->envp) + 2);
	if (!shell->envp)
		return (free(new_var), 1);
	shell->envp[count_envp(shell->envp) - 1] = new_var;
	shell->envp[count_envp(shell->envp)] = NULL;
	return (0);
}

//(TODO) init file, free file, print error? shell exit status?
// run command
// check quotes {} (), test builtins, test tokenizer

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