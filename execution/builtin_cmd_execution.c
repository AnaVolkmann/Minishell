/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:30:07 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/03/15 14:30:12 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin_with_pipe(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped)
{
	int	fd_out[2];

	fd_out[1] = 1;
	if (piped->executed_pipes_index > 1)
		pipe(fd_out);
	env->exit_status = run_command_builtin(cmd_args, env, fd_out);
	if (piped->executed_pipes_index > 1)
	{
		safe_close(fd_out[1]);
		fd[0] = fd_out[0];
	}
	return (free_envp(cmd_args), env->exit_status); // testando
}

int	exec_builtin_with_simple_pipe(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped)
{
	int	fd_out[2];

	fd_out[1] = 1;
	if (piped->is_redirection_or_pipe && piped->has_output_file)
		fd_out[1] = piped->current_output_fd;
	if (piped->executed_pipes_index > 1 && (!piped->is_redirection_or_pipe || !piped->has_output_file))
		pipe(fd_out);
			env->exit_status = run_command_builtin(cmd_args, env, fd_out);
	if (piped->is_redirection_or_pipe && piped->has_output_file)
	{
		safe_close(fd_out[1]);
		piped->has_output_file = 0;
	}
	if (!piped->has_input_file && !piped->has_output_file)
		piped->is_redirection_or_pipe = 0;
	if (piped->executed_pipes_index > 1 && (!piped->is_redirection_or_pipe || !piped->has_output_file))
	{
		safe_close(fd_out[1]);
		fd[0] = fd_out[0];
	}
	return (free_envp(cmd_args), env->exit_status);
}

int	manage_single_builtin_execution(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped)
{
	int	ex_status;

	if (str_cmp(cmd_args[0], "exit", NULL))
	{
		ex_status = 0;
		if (cmd_args[1] && cmd_args[2])
			return (free_envp(cmd_args), 1); // testando
		if (cmd_args[1] && !is_string_numeric(cmd_args[1]))
			ex_status = 255;
		else if (cmd_args[1])
			ex_status = string_to_int(cmd_args[1]);
		free_envp(cmd_args);
		ft_putendl_fd("EXIT", 1);
		cleanup_and_exit_shell(env, ex_status);
	}
	// else if (command_is_builtin(cmd_args[0]))
	// 	env->exit_status = run_command_builtin(cmd_args, env, fd);
	else if (!piped->is_redirection_or_pipe)
	 	env->exit_status = exec_builtin_with_pipe(cmd_args, fd, env, piped);
	else
	 	env->exit_status = exec_builtin_with_simple_pipe(cmd_args, fd, env, piped);
	return (free_envp(cmd_args), env->exit_status); // testando
}
