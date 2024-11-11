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
 * otherwise the variable is appended to the array
 * NEED TO PROTECT THE LAST REALLOC
 * in case the memory alloc fails, we lose the envp ptr
 * so maybe try to alloc in another char** and if correct
 * frees the old one. LINE COUNT :(*/
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
			remove_env(shell->envp, index);
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
	return (free(new_var), 0);
}

//(TODO) expand cases, test tokenizer, check quotes {} (), test builtins and fix leaks
// GCC use on Makefile? check functionality for GNL(missing gnl_utils) and ft_printf.
//if inside quotes, dont expand, but run command if its exactly it.
//"ls" -l works "ls -l" no, neither "ls " -l or "ls"-l
/* testes: cd tem leaks, um de 3k +, que acredito ser da setenv
	export tem leaks (tbm acredito da set env) mas se for atribuido um valor, tem um leak a mais
	pwd tá ok.
	setenv, confirmado leak ser daqui, tem 3k cada valor atribuido, provavelmente por realloc da envp
	unset: tem os mesmos 3k de leak
	
	int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell shell;

	shell.envp = init_dinam_env(envp);
	ft_unset("LUCAS", &shell);
	free(shell.envp);
	return (0);
}*/