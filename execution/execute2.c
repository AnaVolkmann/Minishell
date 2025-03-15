/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:31:32 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/03/15 14:31:34 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Checks if the given command is a shell builtin.
 *
 * @param cmd The command to check.
 * @return `1` if the command is a builtin, `0` otherwise.*/
int	command_is_builtin(char *cmd)
{
	char	*tmp_cmd;
	int		status;

	status = 0;
	tmp_cmd = malloc(sizeof_str(cmd, ' ') + 1);
	if (!tmp_cmd)
		return (0);
	ft_strcopy(tmp_cmd, cmd, 0, sizeof_str(cmd, ' '));
	if (str_cmp(tmp_cmd, "echo", "cd")
		|| str_cmp(tmp_cmd, "pwd", "export")
		|| str_cmp(tmp_cmd, "unset", "env")
		|| str_cmp(tmp_cmd, "exit", NULL))
		status = 1;
	free(tmp_cmd);
	return (status);
}

/** @brief Safely closes the read and write ends of a pipe.
 *
 * @param read_fd File descriptor for the read end.
 * @param write_fd File descriptor for the write end.*/
void	close_pipe_ends(int read_fd, int write_fd)
{
	if (read_fd != -1)
		close(read_fd);
	if (write_fd != -1)
		close(write_fd);
}

/** @brief Executes a command without redirection or complex piping.
 *
 * @param cmd Array containing the command and its arguments.
 * @param fd File descriptor for pipe communication.
 * @param env Array of environment variables.
 * @param piped Pointer to the pipe state structure.
 * @return `1` on success; handles process exit on failure.*/
int	execute_basic_cmd(char **cmd, int *fd, t_env *env, t_pipe_state *piped)
{
	pid_t	pid;
	int		pipe_fds[2];

	pipe(pipe_fds);
	pid = fork();
	signal(SIGINT, child_ctrl_c);
	signal(SIGQUIT, child_ctrl_c);
	if (!pid && !command_is_builtin(cmd[0]))
	{
		if (piped->executed_pipes_index
			&& piped->executed_pipes_index <= piped->pipes_count)
			dup2(fd[0], 0);
		if (piped->executed_pipes_index > 1)
			dup2(pipe_fds[1], 1);
		else
			safe_close(fd[0]);
		close_pipe_ends(pipe_fds[0], pipe_fds[1]);
		execve(cmd[0], cmd, env->parsed_env);
		ft_putendl_fd(strerror(errno), 2), exit(127);
	}
	close_pipe_ends(pipe_fds[1], fd[0]);
	if (piped->executed_pipes_index > 1)
		fd[0] = pipe_fds[0];
	else
		safe_close(pipe_fds[0]);
	return (1);
}

/** @brief Executes a command with file redirection support.
 *
 * @param cmd Array containing the command and its arguments.
 * @param fd File descriptor for pipe communication.
 * @param env Array of environment variables.
 * @param piped Pointer to the pipe state structure.
 * @return `1` on success; handles process exit on failure.*/
int	execute_cmd_with_redirect(char **cmd, int *fd, t_env *env,
	t_pipe_state *piped)
{
	pid_t	pid;
	int		pipe_fds[2];

	pipe(pipe_fds);
	pid = fork();
	signal(SIGINT, child_ctrl_c);
	signal(SIGQUIT, child_ctrl_c);
	if (!pid && !command_is_builtin(cmd[0]))
	{
		child_fds_managment(piped, fd, pipe_fds);
		execve(cmd[0], cmd, env->parsed_env);
		ft_putendl_fd(strerror(errno), 2);
		exit(127);
	}
	parent_fds_managment(piped, fd, pipe_fds);
	free_envp(cmd);
	return (1);
}

