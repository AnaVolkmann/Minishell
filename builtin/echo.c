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

static int	check_flag(char *str);

int	echo(char **args, int argc, int fd, t_shell *shell)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (fd < 0 || write(fd, "\n", 1) == -1)
		return (update_exit(1, shell), perror("echo"), 1);
	if (!args || argc == 0)
		return (write (fd, "\n", 1), update_exit(0, shell), 0);
	while (i < argc && check_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (i < argc - 1)
	{
		write(fd, args[i], ft_strlen(args[i]));
		write(fd, " ", 1);
		i++;
	}
	if (i < argc)
		write(fd, args[i], ft_strlen(args[i]));
	if (newline != 0)
		write(fd, "\n", 1);
	return (update_exit(0, shell), 0);
}

static int	check_flag(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
				return (0);
		}
	return (1);
}
