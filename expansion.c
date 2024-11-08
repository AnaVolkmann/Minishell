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

char	*expansion(char *path)
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
	env_value = getenv(var_name);
	if (env_value != NULL)
		return (ft_strdup(env_value));
	return (NULL);
}

//$?: Exit status of the last command
//$$: Current process ID.
//$!: PID of the last background job.
// do i need to handle VAR="Hello" and echo ${VAR}world to "Hello world"?
// also handle {}?