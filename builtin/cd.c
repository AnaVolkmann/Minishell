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

int	ft_cd(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

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
	old_pwd = getenv("PWD");
	if (chdir(path) != 0)
		return (printf("cd: %s: %s\n", path, strerror(errno)), 1);
	new_pwd = ft_pwd();
	if (old_pwd != NULL)
		ft_setenv("OLDPWD", old_pwd, shell, 1);
	ft_setenv("PWD", new_pwd, shell, 1);
	return (free (new_pwd), printf("Changed Directory to: %s\n", path), 0);
}
