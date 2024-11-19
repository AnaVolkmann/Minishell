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
	char	**keysplit;
	char	*new_var;

	if (!path || !shell || !shell->envp)
		return (-1);
	keysplit = ft_split(path, '=');
	if (!keysplit || !keysplit[0] || ft_strcmp(keysplit[0], path) == 0)
		return (printf("export: %s : not a valid path.\n", path), -1);
	new_var = ft_strdup(path);
	if (!new_var)
		return (free_envp(keysplit), -1);
	i = find_env(shell->envp, keysplit[0]);
	if (i >= 0)
	{
		free(shell->envp[i]);
		shell->envp[i] = new_var;
	}
	else
	{
		i = count_envp(shell->envp);
		shell->envp = realloc_envp(shell->envp, i + 2);
		if (!shell->envp)
			return (free_envp(keysplit), free(new_var), -1);
		shell->envp[i] = new_var;
		shell->envp[i + 1] = NULL;
	}
	return (free_envp(keysplit), 0);
}
