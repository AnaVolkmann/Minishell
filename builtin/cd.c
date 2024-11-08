/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:22:23 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 11:55:14 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *path, char **envp)
{
	//char	*old_pwd;
	(void)envp;
	if (path == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
			return (printf("Error: HOME unset\n"), 1);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			return (printf("Error: OLDPWD unset\n"), 1);
	}
	//old_pwd = getenv("PWD");
	if (chdir(path) != 0)
		return (printf("cd: %s: %s\n", path, strerror(errno)), 1);
	//if (old_pwd != NULL)
	//	ft_setenv("OLDPWD", old_pwd, 1);
	if (ft_pwd() != 0)
		return (1);
	return (printf("Changed Directory to: %s\n", path), 0);
}
