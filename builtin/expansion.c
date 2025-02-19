/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:44:25 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/19 11:36:02 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_utils(char *path,
				t_env *env, char *env_value);

/** @brief handles edge cases and searches the env var inside the shell's envp
 * if it not finds it, returns an error
 * the function caller needs to free is return value */
char	*expansion(char *path, t_env *env)
{
	char	*env_value;

	env_value = NULL;
	if (!path || !path[0])
		return (update_exit(1, env), NULL);
	if (path[0] == '"')
	{
		env_value = expand_utils(path, env, env_value);
		if (!env_value)
			return (update_exit(1, env), NULL);
	}
	if (path[0] == '\'')
		return (update_exit(0, env), ft_strdup(path));
	if (ft_strcmp(path, "$$") == 0)
		return (update_exit(0, env), ft_itoa(env->pid));
	if (ft_strcmp(path, "$?") == 0)
		return (update_exit(0, env), ft_itoa(env->exit_status));
	if (ft_strcmp(path, "$!") == 0)
		return (update_exit(0, env), ft_itoa(env->last_pid));
	if (env_value)
		return (update_exit(0, env), ft_strdup(env_value));
	env_value = get_env(path, env->parsed_env);
	if (!env_value)
		return (update_exit(1, env), NULL);
	return (update_exit(0, env), ft_strdup(env_value));
}

static char	*expand_utils(char *path,
				t_env *env, char *env_value)
{
	char	**split;
	int		i;

	i = -1;
	while (path[0] == '"')
		ft_strtrim(path, "\"");
	split = ft_split(path, ' ');
	if (!split)
		return (NULL);
	while (split[++i])
	{
		env_value = ft_strjoin(env_value, expansion(split[i], env));
		if (!env_value)
			return (free_envp(split), update_exit(1, env), NULL);
	}
	return (env_value);
}
