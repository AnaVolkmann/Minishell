/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:07:48 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief separates the path as in KEY=value
 * then sets the env*/
int	ft_export(char *path, t_shell *shell)
{
	int		i;
	int		count;
	char	*new_var;

	if (!path || !shell || !shell->envp)
		return (-1);
	new_var = ft_strdup(path);
	if (!new_var)
		return (-1);
	i = find_env(shell->envp, path);
	if (i >= 0)
	{
		free(shell->envp[i]);
		shell->envp[i] = new_var;
	}
	else
	{
		count = count_envp(shell->envp);
		shell->envp = realloc_envp(shell->envp, count + 2);
		if (!shell->envp)
			return (-1);
	}
	shell->envp[count] = new_var;
	shell->envp[count + 1] = NULL;
	return (0);
}
