/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:12:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/18 17:18:30 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **args, int argc, int fd)
{
	int	i;

	i = 0;
	if (argc == 0)
	{
		write(fd, "\n", 1);
		return (0);
	}
	while (args[i] && !ft_strcmp(args[i], "-n"))
		i++;
	while (i < argc - 1)
	{
		write(fd, args[i], strlen(args[i]));
		write(fd, " ", 1);
		i++;
	}
	if (i < argc)
	{
		write(fd, args[i], strlen(args[i]));
	}
	if (ft_strcmp(args[0], "-n") != 0)
		write(fd, "\n", 1);
	return (0);
}
