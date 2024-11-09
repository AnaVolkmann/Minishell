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

// duplicate the envp variable so i can change it 
// freely without messing with something else
// envp works as KEY=VALUE
// look up for the value you want, if you find it, delete, if not, all good
// the delete works as in a swap, you overwrite the one you want to "delete", 
// and shift everything else on top of it

#include "../minishell.h"

int	ft_unset(char *path, char **envp)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(path);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], path, len) == 0 && envp[i][len] == '=')
		{
			free (envp[i]);
			j = i;
			while (envp[j] != NULL)
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j - 1] = NULL;
			return (0);
		}
		i++;
	}
	return (-1);
}

static char	**realloc_envp(char **envp, int size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = (char **)malloc(sizeof(char *) * size);
	if (!new_envp)
		return (NULL);
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = NULL;
	free (envp);
	return (new_envp);
}

static char	*new_env_var(char *name, char *value)
{
	int		len;
	char	*new_var;

	if (name == NULL || value == NULL)
		return (NULL);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = (char *)malloc(sizeof(char) * len);
	if (new_var == NULL)
		return (NULL);
	new_var[0] = '\0';
	ft_strlcat(new_var, name, len);
	ft_strlcat(new_var, "=", len);
	ft_strlcat(new_var, value, len);
	return (new_var);
}

int	ft_setenv(char *name, char *value, t_shell shell, int overwrite)
{
	int		i;
	int		len;
	char	*new_var;

	if (!name || !value || !shell || !shell->envp)
		return (1);
	i = 0;
	len = ft_strlen(name);
	new_var = new_env_var(name, value);
	if (!new_var)
		return (1);
	while (shell->envp[i])
	{
		if (strncmp(shell->envp[i], name, len) == 0 && shell->envp[i][len] == '=')
		{
			if (overwrite == 1)
			{
				free(shell->envp[i]);
				shell->envp[i] = new_var;
			}
			else
				free (new_var);
			return (0);
		}
		i++;
	}
	shell->envp = realloc_envp(shell->envp, i + 2);
	if (!shell->envp)
		return (free(new_var), 1);
	shell->envp[i] = new_var;
	return (0);
}

//(TODO) Finish unset, get cd working with it, expand cases, 
//test tokenizer, check quotes {} ()
// if inside quotes, dont expand, but run command if its exactly it.
//"ls" -l works "ls -l" no, neither "ls " -l or "ls"-l
