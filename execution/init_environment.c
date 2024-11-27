/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:21:20 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/27 18:46:37 by ana-lda-         ###   ########.fr       */
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

int	wait_for_children(int status, t_pipe_state *piped)
{
	if (status != 2 && status != 127
		&& status != 126 && piped->children_count
		&& piped->second_heredoc_status)
	{
		while (piped->children_count)
		{
			wait(&status);
			piped->children_count -= 1;
		}
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		if (!g_signal)
			return (WEXITSTATUS(status));
		else
			return (g_signal);
	}
	return (status);
}
