/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:28:08 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/13 13:28:17 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief searchs for the variable in envp, returns its index if found*/
int	find_env(char **envp, char *name)
{
	int	len;
	int	i;

	if (!name || !envp)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/** @brief removes the env var by its index
 * shifts remaining variables to close the gap*/
void	remove_env(char **envp, int index)
{
	if (!envp || index < 0)
		return ;
	free (envp[index]);
	while (envp[index + 1])
	{
		envp[index] = envp[index + 1];
		index++;
	}
	envp[index] = NULL;
}

/** @brief reallocates memory for a new size envp. 
 * frees the old array and copies it to the new one;*/
char	**realloc_envp(char **envp, int size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = (char **)malloc(sizeof(char *) * size);
	if (!new_envp)
		return (NULL);
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (free_envp(new_envp), NULL);
		i++;
	}
	free_envp (envp);
	new_envp[size - 1] = NULL;
	return (new_envp);
}

/** @brief creates the new env var string;
 *  constructs the string in the format name=value*/
char	*new_env_var(char *name, char *value)
{
	int		len;
	char	*new_var;

	if (!name || !value)
		return (NULL);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = (char *)malloc(sizeof(char) * len);
	if (!new_var)
		return (NULL);
	new_var[0] = '\0';
	ft_strlcat(new_var, name, len);
	ft_strlcat(new_var, "=", len);
	ft_strlcat(new_var, value, len);
	return (new_var);
}

/** @brief it... counts.*/
int	count_envp(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}
