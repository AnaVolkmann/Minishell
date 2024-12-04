/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 15:54:26 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ordered_envp(char **copy);
static char	**copy_envp(char **envp);
static void	export_error(char *path);
static int	ft_add(char	*new_var, t_env *env, char **keysplit);

/** @brief separates the path as in KEY=value
 * then sets the env
 * if no arguments, prints the ordered envp */
int	ft_export(char *path, t_env *env)
{
	char	**keysplit;
	char	*new_var;
	int		i;

	i = 0;
	if (!env->shell || !env->parsed_env)
		return (update_exit(2, env->shell), -1);
	if (!path)
		return (update_exit(0, env->shell), ordered_envp(copy_envp(env->parsed_env)), 0);
	keysplit = ft_split(path, '=');
	if (!keysplit || !keysplit[0])
		return (update_exit(2, env->shell), export_error(path), -1);
	while (keysplit[i])
		i++;
	if (i != 2)
		return (update_exit(2, env->shell), 1);
	new_var = ft_strdup(path);
	if (!new_var)
		return (update_exit(1, env->shell), free_envp(keysplit), -1);
	if (ft_add(new_var, env->shell, keysplit) != 0)
		return (1);
	return (update_exit(0, env->shell), free_envp(keysplit), 0);
}

/** @brief looks for the variable inside envp
 * if it finds it, just replaces it with the new value one
 * otherwise it reallocates the whole envp to fit the new variable */
static int	ft_add(char	*new_var, t_env *env, char **keysplit)
{
	int	i;

	i = find_env(env->parsed_env, keysplit[0]);
	if (i >= 0)
	{
		free(env->parsed_env[i]);
		env->parsed_env[i] = new_var;
	}
	else
	{
		i = count_envp(env->parsed_env);
		env->parsed_env = realloc_envp(env->parsed_env, i + 2);
		if (!env->parsed_env)
			return (update_exit(1, env->shell),
				free_envp(keysplit), free(new_var), -1);
		env->parsed_env[i] = new_var;
		env->parsed_env[i + 1] = NULL;
	}
	return (0);
}

/** @brief does a copy of the envp, that we can use to alter (or order maybe)*/
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

/** @brief does a pseudo bubble sort algorithm to order the envp
 * at the end prints it whole */
static void	ordered_envp(char **copy)
{
	int		i;
	char	*tmp;

	i = 0;
	while (copy[i] && copy[i + 1])
	{
		if (ft_strcmp(copy[i], copy[i + 1]) > 0)
		{
			tmp = copy[i];
			copy[i] = copy[i + 1];
			copy[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = -1;
	while (copy[++i])
		printf("%s\n", copy[i]);
	free_envp(copy);
}

static void	export_error(char *path)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}
