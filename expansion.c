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

int	expansion(char *path)
{
	int	i;
	int	j;
	char	var_name[256];

	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] == '$')
		{
			i++;
			while ((path[i] == '_' || isalnum(path[i])) && path[i])
				var_name[j++] = path[i++];
			var_name[j] = '\0';
		}
		i++;
	}
	return (printf("%s\n", getenv(var_name)), 0);
}
