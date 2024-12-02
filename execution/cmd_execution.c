/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:11:12 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 17:49:21 by ana-lda-         ###   ########.fr       */
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
void close_pipe_ends(int read_fd, int write_fd)
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
int	execute_basic_cmd(char **cmd, int *fd, char **env, t_pipe_state *piped)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	signal(SIGINT, child_ctrl_c);
	signal(SIGQUIT, child_ctrl_c);
	if (pid == 0)
	{
		if (piped->executed_pipes_index && piped->executed_pipes_index <= 5)
			dup2(fd[0], 0);
		if (piped->executed_pipes_index > 1)
			dup2(fd[1], 1);
		else
			close(fd[0]);
		close_pipe_ends(fd[0], fd[1]);
		execve(cmd[0], (char *const *)cmd, env);
		//   ft_putendl_fd(strerror(errno), 2);
        //  exit(127);
	}
	close_pipe_ends(fd[0], fd[1]);
	if (piped->executed_pipes_index < piped->pipes_count && piped->pipes_count > 1)
		fd[0] = fd[0];
	else
		close(fd[0]);
	return (1);
}

/** @brief Executes a command with file redirection support.
 * 
 * @param cmd Array containing the command and its arguments.
 * @param fd File descriptor for pipe communication.
 * @param env Array of environment variables.
 * @param piped Pointer to the pipe state structure.
 * @return `1` on success; handles process exit on failure.*/
int	execute_cmd_with_redirect(char **cmd, int *fd, char **env, t_pipe_state *piped)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	signal(SIGINT, child_ctrl_c);
	signal(SIGQUIT, child_ctrl_c);
	if (!pid)
	{
		manage_child_fds(piped, fd, fd);
		execve(cmd[0], cmd, env);
		// ft_putendl_fd(strerror(errno), 2);
		//exit(127);
	}
	manage_parent_fds(piped, fd, fd);
	free_envp(cmd);
	return (1);
}
