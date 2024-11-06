/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:22:23 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/03 13:29:16 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(char	*path)
{
	if (path == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
			return (printf("Error: HOME unset\n"), 1);
	}
	if (chdir(path) != 0)
		return (printf("cd: %s: %s\n", path, strerror(errno)), 1);
	return (printf("Changed Directory to: %s\n", path), 0);
	
}
