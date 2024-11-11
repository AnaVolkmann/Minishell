/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:56 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/07 12:44:40 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(t_shell *shell, char **original_env)
{
	shell->pid = getpid();
	shell->path = NULL;
	shell->envp = init_dinam_env(original_env);
	shell->input = NULL;
	return (shell);
}

char	**init_dinam_env(char **original_env)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while(original_env[j])
		j++;
	new_envp = malloc(sizeof(char *) * (j + 1));
	if (!new_envp)
		return (NULL);
	while (original_env[i])
	{
		new_envp[i] = ft_strdup(original_env[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free (new_envp[i]);
			return (free(new_envp), NULL);
		}
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}
