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

int	main()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	
	if (pwd != NULL)
		return (printf("%s\n", pwd), free(pwd), 0);
	else
		return (printf("Error: getcwd()\n"),free(pwd), 1);
}
