/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:58:59 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/19 11:37:34 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief allocates memory with getcwd, the caller must free its return value
 * 	it has a flag that makes it print or not ( for cd use ) */
static void	pwd_error(void);

char	*ft_pwd(t_env *env, int flag)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (update_exit(1, env), pwd_error(), NULL);
	if (flag == 1)
		return (update_exit(0, env), printf("%s\n", pwd), pwd);
	return (update_exit(0, env), pwd);
}

static void	pwd_error(void)
{
	ft_putstr_fd("Error: getcwd() failed: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
