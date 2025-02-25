/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:27:54 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/25 12:31:05 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Manages file descriptors for a child process,
 * handling pipes and redirections.
 *
 * @param piped Pipe state structure with redirection and piping info.
 * @param _fd File descriptors for the previous pipe.
 * @param fd_ File descriptors for the current pipe.*/
void	child_fds_managment(t_pipe_state *piped, int *_fd, int *fd_)
{
	if (piped->is_redirection_or_pipe && piped->has_input_file)
	{
		dup2(piped->input_files_count, 0);
		close(piped->input_files_count);
	}
	if (piped->is_redirection_or_pipe && piped->has_output_file)
	{
		dup2(piped->output_files_count, 1);
		close(piped->output_files_count);
	}
	if (piped->executed_pipes_index
		&& piped->executed_pipes_index <= piped->current_output_fd
		&& (!piped->is_redirection_or_pipe || !piped->has_input_file))
		dup2(_fd[0], 0);
	if (piped->executed_pipes_index > 1
		&& (!piped->is_redirection_or_pipe || !piped->has_output_file))
		dup2(fd_[1], 1);
	else
		close(fd_[0]);
	close(fd_[0]);
	close(fd_[1]);
}

/** @brief Manages file descriptors for a parent process,
 * cleaning up pipes and redirections.
 *
 * @param piped Pipe state structure with redirection and piping info.
 * @param _fd File descriptors for the previous pipe.
 * @param fd_ File descriptors for the current pipe.*/
void	parent_fds_managment(t_pipe_state *piped, int *_fd, int *fd_)
{
	if (piped->is_redirection_or_pipe && piped->has_input_file)
	{
		close(piped->input_files_count);
		piped->has_input_file = 0;
	}
	if (piped->is_redirection_or_pipe && piped->has_output_file)
	{
		close(piped->output_files_count);
		piped->has_output_file = 0;
	}
	if (!piped->has_output_file && !piped->has_input_file)
		piped->is_redirection_or_pipe = 0;
	close(fd_[1]);
	close(_fd[0]);
	if (piped->executed_pipes_index > 1)
		_fd[0] = fd_[0];
	else
		close(fd_[0]);
}
