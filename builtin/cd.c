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

static int	set_pwd(char *path, t_shell *shell);

int	ft_cd(char *path, t_shell *shell)
{
	if (path == NULL || ft_strncmp(path, "~", 2) == 0)
	{
		path = get_env("HOME", shell->envp);
		if (path == NULL)
			return (printf("Error: HOME unset\n"), 1);
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = get_env("OLDPWD", shell->envp);
		if (path == NULL)
			return (printf("Error: OLDPWD unset\n"), 1);
	}
	set_pwd(path, shell);
	return (0);
}

static int	set_pwd(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*export;

	old_pwd = get_env("PWD", shell->envp);
	if (chdir(path) != 0)
		return (printf("cd: %s: %s\n", path, strerror(errno)), 1);
	//if (access(path, F_OK) != 0)
	//	return (printf("cd: %s: No such file or directory\n", path), 1);
	if (old_pwd)
	{
		export = new_env_var("OLDPWD", old_pwd);
		if (!export)
			return (1);
		ft_export(export, shell);
		free(export);
	}
	new_pwd = ft_pwd();
	if (!new_pwd)
		return (1);
	export = new_env_var("PWD", new_pwd);
	if (!export)
		return (free (new_pwd), 1);
	ft_export(export, shell);
	return (free (export), free (new_pwd), 0);
}
