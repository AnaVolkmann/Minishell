/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:21:20 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/27 17:34:06 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_or_reset_pipe_state(t_pipe_state *pipe_state, int f)
{
	pipe_state->executed_pipes_index = pipe_state->pipes_count;

	if (f)
	{
		pipe_state->executed_pipes_index = 0;
		pipe_state->input_files_count = 0;
		pipe_state->output_files_count = 0;
		pipe_state->pipes_count = 0;
		pipe_state->current_input_fd = 0;
		pipe_state->current_output_fd = 0;
		pipe_state->has_input_file = 0;
		pipe_state->has_output_file = 0;
		pipe_state->is_redirection_or_pipe = 0;
		pipe_state->heredoc_status = 0;
		pipe_state->children_count = 0;
		pipe_state->second_heredoc_status = 0;
	}
	else if (pipe_state->pipes_count)
		pipe_state->executed_pipes_index += 1;
	pipe_state->second_heredoc_status = 1;
}
