/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:11:12 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 16:12:25 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void close_pipe_ends(int read_fd, int write_fd)
{
	if (read_fd != -1)
		close(read_fd);
	if (write_fd != -1)
		close(write_fd);
}

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
		execve(cmd[0], cmd, env);
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
