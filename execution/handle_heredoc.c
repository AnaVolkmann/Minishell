/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:24:12 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/27 18:40:01 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quite_heredoc(int n)
{
	(void)n;
	write(1, "\n", 1);
	exit(0);
}

int	have_quotes(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

void	read_and_write(t_pipe_state *pipe_state, char *limiter, t_env *env, int is_expandable)
{
	char *buf;
	int f_arr[3];

	limiter = remove_quotes_from_str(limiter, 0, 0, 0);
	while (1)
	{
		buf = readline(">> ");
		if (!buf || str_compare(limiter, buf, sizeof_str(buf, '\n')))
		{
			free(buf);
			break;
		}
		if (is_expandable)
		{
			buf[sizeof_str(buf, '\n')] = '\0';
			ft_memset(f_arr, 0, 3 * sizeof(int));
			buf = recursively_expand_variables(buf, env, 0, f_arr);
			ft_memset(f_arr, 0, 3 * sizeof(int));
			buf = recursively_expand_variables(buf, env, 1, f_arr);
		}
		write(pipe_state->current_output_fd, buf, sizeof_str(buf, '\0'));
		write(pipe_state->current_output_fd, "\n", 1);
		free(buf);
	}
	free(limiter);
}

int	exec_here_doc(char *limiter, t_pipe_state *pipe_state, t_env *env)
{
	pid_t	pid;
	int		status;
	int		out_fd[2];

	pipe(out_fd);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, quite_heredoc);
		close(out_fd[0]);
		read_and_write(out_fd[1], limiter, env, have_quotes(limiter));
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(out_fd[1]);
	pipe_state->current_input_fd = out_fd[0];
	pipe_state->heredoc_status = (WEXITSTATUS(status)) - 1;
	if (pipe_state->heredoc_status < 0)
		pipe_state->heredoc_status += 2;
	pipe_state->second_heredoc_status = status;
	return (pipe_state->heredoc_status);
}
