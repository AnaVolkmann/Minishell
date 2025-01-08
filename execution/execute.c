/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:18:13 by lufiguei          #+#    #+#             */
/*   Updated: 2024/12/04 16:40:46 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief it compares the command with all 7 builtins
 * if any match is found, it runs the command with its argument, otherwise
 * it returns -1 to signalize that it didnt ran */
int	run_command_builtin(char **arguments, t_env *env, t_shell *shell)
{
	int		i;
	char	*pwd;

	i = 0;
	while (arguments[i])
		i++;
	if (ft_strcmp(arguments[0], "cd") == 0)
		return (ft_cd(arguments[1], env), 0);
	else if (ft_strcmp(arguments[0], "echo") == 0)
		return (echo(arguments + 1, i, shell->output_fd, shell), 0);
	else if (ft_strcmp(arguments[0], "env") == 0)
		return (ft_env(env), 0);
	else if (ft_strcmp(arguments[0], "exit") == 0)
		return (bash_exit(arguments + 1, i, shell), 0);
	else if (ft_strcmp(arguments[0], "export") == 0)
		return (ft_export(arguments[1], env), 0);
	else if (ft_strcmp(arguments[0], "pwd") == 0)
	{
		pwd = ft_pwd(shell, 1);
		return (free(pwd), 0);
	}
	else if (ft_strcmp(arguments[0], "unset") == 0)
		return (ft_unset(arguments[1], env), 0);
	return (-1);
}

/** @brief it splits the PATH variable ":" and tries to access the
 * command to see if its inside this path. if not, frees and goes to
 * the next. if it find it, returns the full path, otherwise
 * it returns NULL 
static char	*loop_path(char *cmd, char *path_env)
{
	char	**path;
	char	*full_path;
	int		i;

	i = 0;
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		full_path = malloc(ft_strlen(path[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
			return (NULL);
		ft_memcpy(full_path, path[i], ft_strlen(path[i]));
		full_path[ft_strlen(path[i])] = '/';
		ft_memcpy(full_path + ft_strlen(path[i]) + 1, cmd, ft_strlen(cmd) + 1);
		if (access(full_path, X_OK) == 0)
			return (free_envp(path), full_path);
		free(full_path);
		i++;
	}
	free_envp(path);
	return (NULL);
}

 @brief checks if the command is already an absolute "/" 
 * or an relative "." path if not, 
 * it calls the loop_path to find the program
static char	*get_path(char *cmd, char **envp)
{
	char	*cmd_path;
	char	*full_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	cmd_path = get_env("PATH", envp);
	if (!cmd_path) // *cmd_path == '\0'?
		return (printf("PATH environment variable is not set.\n"), NULL);
	full_path = loop_path(cmd, cmd_path);
	return (free(cmd_path), full_path);
}

@brief it runs the execve commands 
static int	run_command_exec(char *cmd, char *const *argument, t_shell *shell)
{
	char	*cmd_path;

	cmd_path = get_path(cmd, shell->envp);
	if (!cmd_path)
		return (printf("Command not found: %s\n", cmd), 1);
	if (execve(cmd_path, argument, shell->envp) == -1)
		return (free(cmd_path), printf("execve: %s: %s\n",
				cmd, strerror(errno)), 1);
	return (free(cmd_path), 0);
}

@brief it first tries to execute the builtin functions, 
 * if its not inside that, it straight up goes to execve, 
 * returns error if none found
int	execute(char *cmd, char *const *argument, t_shell *shell)
{
	if (run_command_builtin((char **)argument, shell) == 0)
		return (0);
	else if (run_command_exec(cmd, argument, shell) == 0)
		return (0);
	return (1);
}*/
