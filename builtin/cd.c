/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:22:23 by lufiguei          #+#    #+#             */
/*   Updated: 2024/12/04 16:21:59 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_pwd(char *path, t_env *env);
static int	cd_error(char *path);

/** @brief handles the edge cases and calls the set pwd function to update env
*/
int	ft_cd(char *path, t_env *env)
{
	char	*tmp;

	if (path == NULL || ft_strncmp(path, "~", 2) == 0)
	{
		tmp = get_env("HOME", env->parsed_env);
		if (tmp == NULL)
			return (update_exit(1, env->shell),
				ft_putstr_fd("Error: HOME unset\n", 2), 1);
		return (set_pwd(tmp, env), free (tmp), update_exit(0, env->shell), 0);
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		tmp = get_env("OLDPWD", env->parsed_env);
		if (tmp == NULL)
			return (update_exit(1, env->shell),
				ft_putstr_fd("Error: OLDPWD unset\n", 2), 1);
		set_pwd(tmp, env);
		return (printf("%s\n", tmp), free(tmp), update_exit(0, env->shell), 0);
	}
	if (set_pwd(path, env) != 0)
		return (update_exit(1, env->shell), 1);
	return (update_exit(0, env->shell), 0);
}

/** @brief updates OLD PWD and PWD. first it saves the pwd to char *old pwd
 * then tries to change dir (it fails if no permission)
 * then updates old pwd 
 * it then gets the new pwd value and updates the env 
 * what if pwd is unset?  */
static int	set_pwd(char *path, t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*export;

	old_pwd = get_env("PWD", env->parsed_env);
	if (chdir(path) != 0)
		return (cd_error(path), free (old_pwd), 1);
	if (old_pwd)
	{
		export = new_env_var("OLDPWD", old_pwd);
		if (!export)
			return (free (old_pwd), 1);
		ft_export(export, env);
		free(export);
	}
	new_pwd = ft_pwd(env->shell, 0);
	if (!new_pwd)
		return (ft_putstr_fd("Error: Unable to fetch current directory\n", 2),
			free (old_pwd), 1);
	export = new_env_var("PWD", new_pwd);
	if (!export)
		return (free (old_pwd), free (new_pwd), 1);
	ft_export(export, env);
	return (free (old_pwd), free (export), free (new_pwd), 0);
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
