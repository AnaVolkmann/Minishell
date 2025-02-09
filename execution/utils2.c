/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:44:03 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/09 11:44:26 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Initializes or resets the state of the pipe system
 * for command execution.
 * Resets pipe and redirection tracking fields, or increments
 * the executed pipes index based on the flag.
 *
 * @param pipe_state Structure managing the current pipe and redirection state.
 * @param f Flag indicating the reset mode
 * (1 for full reset, 0 for partial update).*/
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
		pipe_state->second_heredoc_status = 0; // settar direto pra 1?
	}
	else if (pipe_state->pipes_count)
		pipe_state->executed_pipes_index += 1;
	pipe_state->second_heredoc_status = 1;
}

/** @brief Waits for all child processes to finish and
 * returns their exit status.
 * Handles signals and updates the global status variable
 * (`g_signal`) if applicable.
 *
 * @param status Initial status to check against signal conditions.
 * @param piped Pipe state structure tracking the
 * number of active child processes.
 * @return Exit status of the last child process, or the global signal status if
 * interrupted.*/
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
			return (WEXITSTATUS(status)); // funcao permitida?
		else
			return (g_signal);
	}
	return (status);
}

char	*strcopy(char *src)
{
	int		a;
	int		b;
	char	*dest;

	b = 0;
	while (src[b])
		b += 1;
	dest = malloc(b + 1);
	if (!dest)
		return (NULL);
	a = 0;
	while (a < b)
	{
		dest[a] = src[a];
		a += 1;
	}
	dest[a] = '\0';
	return (dest);
}

char	**merge_cmd_args(char **f_args, char **cmd)
{
	int		i;
	char	**new_args;

	if (!f_args)
		return (NULL);
	i = 1;
	while (cmd[0] && cmd[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	if (f_args[i])
		new_args[i] = strcopy(f_args[i]);
	else
		new_args[i] = strcopy("");
	if (cmd && cmd[0])
	{
		while (cmd[++i])
			new_args[i] = strcopy(cmd[i]);
	}
	new_args[i] = 0;
	free_envp(f_args);
	return (new_args);
}

void	is_sus_dir(char *path_, char *file, int *status)
{
	struct stat		s;

	if (file && str_cmp(file, ".", NULL))
		*status = 2;
	else if (str_cmp(file, "..", NULL)
		|| str_cmp(file, ",", ""))
	{
		*status = 1;
		errno = 2;
	}
	else if (!stat(path_, &s)
		&& s.st_mode)
	{
		*status = 2;
		ft_putstr_fd("   err: this \'", 2);
		ft_putstr_fd(path_, 2);
		ft_putendl_fd("\' Is a directory", 2);
		errno = 13;
	}
}

/* int	is_sus_dir(char *path)
{
	char	copy[1024];
	int		i;

	i = 0;
	if (!path)
		return (1);
	while (*path)
	{
		if (path[0] == '.' && path[1] == '.'
			&& (path[2] == '/' || path[2] == '\0'))
		{
			path += 2;
			if (*path == '/')
				path += 1;
		}
		else if (path[0] == '.' && (path[1] == '/' || path[1] == '\0'))
		{
			path += 1;
			if (*path == '/')
				path += 1;
		}
		else
			copy[i++] = *path++;
	}
	copy[i] = '\0';
	if (ft_strcmp(path, copy) != 0)
		return (1);
	return (0);
} */

/* int	check_safety(t_ast_node *head, char *path)
{
	struct stat	s;
	char		*tmp;

	(void)head;//dei void
	tmp = ft_strdup(path);
	if (!tmp)
		return (1);
	if (is_sus_dir(tmp) == 1)
		return (free(tmp), 1);
	if (ft_strcmp(path, "/etc") == 0 || ft_strcmp(path, "/dev") == 0
		|| ft_strcmp(path, "/proc") == 0)
		return (ft_putstr_fd("Error: access denied to restricted directory.\n",
				2), free(tmp), 1);
	if (!is_path_accessible(path, X_OK) || !is_path_accessible(path, F_OK))
		return (ft_putstr_fd("Error: path related.\n", 2), free(tmp), 1);
	if (lstat(path, &s) == -1)
		return (perror("Error getting file info\n"), free(tmp), 1);
	return (free(tmp), 0);
} */
