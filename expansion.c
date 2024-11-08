/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:44:25 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/03 13:56:58 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(char *path, char **envp)
{
	int		i;
	int		j;
	char	var_name[256];
	char	*env_value;

	i = 0;
	j = 0;
	if (path[i] == '$')
	{
		i++;
		while ((path[i] == '_' || ft_isalnum(path[i])) && path[i])
			var_name[j++] = path[i++];
		var_name[j] = '\0';
		if (j == 0)
			return (NULL);
	}
	env_value = get_env(var_name, envp);
	if (env_value != NULL)
		return (ft_strdup(env_value));
	return (NULL);
}
