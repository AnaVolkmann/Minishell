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
static int	cd_error(char *path);

/** @brief handles the edge cases and calls the set pwd function to update env
*/
int	ft_cd(char *path, t_shell *shell)
{
	if (path == NULL || ft_strncmp(path, "~", 2) == 0)
	{
		path = get_env("HOME", shell->envp);
		if (path == NULL)
			return (update_exit(1, shell),
				ft_putstr_fd("Error: HOME unset\n", 2), 1);
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = get_env("OLDPWD", shell->envp);
		if (path == NULL)
			return (update_exit(1, shell),
				ft_putstr_fd("Error: OLDPWD unset\n", 2), 1);
		printf("%s\n", path);
	}
	if (set_pwd(path, shell) != 0)
		return (update_exit(1, shell), 1);
	return (update_exit(0, shell), 0);
}

/** @brief updates OLD PWD and PWD. first it saves the pwd to char *old pwd
 * then tries to change dir (it fails if no permission)
 * then updates old pwd 
 * it then gets the new pwd value and updates the env */
static int	set_pwd(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*export;

	old_pwd = get_env("PWD", shell->envp); // what if pwd is unset?
	if (chdir(path) != 0)
		return (cd_error(path), 1);
	if (old_pwd)
	{
		export = new_env_var("OLDPWD", old_pwd);
		if (!export)
			return (1);
		ft_export(export, shell);
		free(export);
	}
	new_pwd = ft_pwd(shell, 0);
	if (!new_pwd)
		return (ft_putstr_fd("Error: Unable to fetch current directory\n", 2),
			1);
	export = new_env_var("PWD", new_pwd);
	if (!export)
		return (free (new_pwd), 1);
	ft_export(export, shell);
	return (free (export), free (new_pwd), 0);
}

static int	cd_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
