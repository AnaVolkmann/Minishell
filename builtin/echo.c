/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:12:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/19 11:33:23 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *str);

/** @brief it checks for the flag -n, starts the function assuming its "off"
 * while it has arguments, prints them on the FD, in the end checks
 * for the -n flag
*/
int	echo(char **args, int argc, int *fd, t_env *env)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (*fd < 0 || write(*fd, "", 1) == -1)
		return (update_exit(1, env), perror("echo"), 1);
	if (!args || !args[i] || argc == 0)
		return (write (*fd, "\n", 1), update_exit(0, env), 0);
	while (i < argc && args[i] && check_flag(args[i]))
	{
		n = 0;
		i++;
	}
	while (i < argc - 1)
	{
		write(*fd, args[i], ft_strlen(args[i]));
		write(*fd, " ", 1);
		i++;
	}
	if (i < argc)
		write(*fd, args[i], ft_strlen(args[i]));
	if (n != 0)
		write(*fd, "\n", 1);
	return (update_exit(0, env), 0);
}

static int	check_flag(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}
