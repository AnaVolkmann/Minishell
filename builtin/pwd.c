/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:58:59 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/03 13:07:53 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	
	if (pwd == NULL)
		return (printf("Error: getcwd() failed: %s\n", strerror(errno)), 1);
	return (printf("%s\n", pwd), free(pwd), 0);
}
