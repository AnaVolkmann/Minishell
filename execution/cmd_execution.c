/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:11:12 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 15:28:22 by ana-lda-         ###   ########.fr       */
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

int	execute_basic_cmd(char **cmd, int *fd, char **env, t_pipe_state *piped)
{
	pid_t	pid;

	
	

}
