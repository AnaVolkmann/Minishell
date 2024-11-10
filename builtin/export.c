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

static int	key_len(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != '=')
		i++;
	return (i);
}
/** @brief separates the path as in KEY=value
 * then sets the env*/
int	ft_export(char *path, t_shell shell)
{
	int		i;
	char	*value;
	char	*key;

	i = key_len(path);
	if (path[i] != '=')
		return (printf("Export: invalid format: use KEY=VALUE\n"), -1);
	key = ft_substr(path, 0, i);
	value = ft_strdup(&path[i + 1]);
	if (!key || !value)
	{
		printf("Error: memory allocation failed: %s.\n", strerror(errno));
		return (free (key), free(value), -1);
	}
	if (ft_setenv(key, value, shell, 1) != 0)
		return (free (key), free (value), 1);
	return (free(key), free(value), 0);
}
