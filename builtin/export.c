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

static void	swap(char **s1, char **s2);
static void	ordered_envp(char **copy);
static char	**copy_envp(char **envp);
static void	export_error(char *path);

/** @brief separates the path as in KEY=value
 * then sets the env*/
int	ft_export(char *path, t_shell *shell)
{
	int		i;
	char	**keysplit;
	char	*new_var;

	if (!shell || !shell->envp)
		return (update_exit(2, shell), -1);
	if (!path)
		return (update_exit(0, shell), ordered_envp(copy_envp(shell->envp)), 0);
	keysplit = ft_split(path, '=');
	if (!keysplit || !keysplit[0] || ft_strcmp(keysplit[0], path) == 0)
		return (update_exit(2, shell), export_error(path), -1); //exit status 2?
	new_var = ft_strdup(path);
	if (!new_var)
		return (update_exit(1, shell), free_envp(keysplit), -1);
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
			return (update_exit(0, shell),
				free_envp(keysplit), free(new_var), -1);
		shell->envp[i] = new_var;
		shell->envp[i + 1] = NULL;
	}
	return (update_exit(0, shell), free_envp(keysplit), 0);
}

static char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (free_envp(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	ordered_envp(char **copy)
{
	int	i;

	i = 0;
	while (copy[i] && copy[i + 1])
	{
		if (ft_strcmp(copy[i], copy[i + 1]) > 0)
		{
			swap(copy[i], copy[i + 1]);
			i = 0;
		}
		i++;
	}
	i = 0;
	while (copy[i])
		printf("%s\n", copy[i]);
	free_envp(copy);
}

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	export_error(char *path)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}
