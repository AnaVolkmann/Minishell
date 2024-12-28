/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:14:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/04 17:40:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Parses command arguments, handles built-in commands,
 * and executes external commands.
 * Also manages redirection or pipe states during execution.
 *
 * @param cmd Command arguments as a string array.
 * @param fd File descriptors for input/output redirection.
 * @param piped Pipe state structure containing redirection and piping info.
 * @param env Environment variables and shell state.
 * @return Execution status code.*/
int	prepare_and_execute_cmd(char **cmd, int *fd, t_pipe_state *piped,
	t_env *env)
{
	char	**cmd_args;
	char	**f_args;
	int		status;

	f_args = prepare_cmd_args(cmd[0], env->original_env, 0);
	cmd_args = merge_cmd_args(f_args, cmd);
	if (command_is_builtin(cmd_args[0]))
		status = run_command_builtin(cmd_args, env, env->shell);
	else
	{
		piped->children_count += 1;
		if (!piped->is_redirection_or_pipe)
		{
			status = execute_basic_cmd(cmd_args, fd, env->original_env, piped);
			free_envp(cmd_args); // testar leacks
		}
		else
			status = execute_cmd_with_redirect(cmd_args, fd,
					env->original_env, piped);
	}
	if (piped->executed_pipes_index > 1)
		piped->executed_pipes_index -= 1;
	return (status);
}

/** @brief Opens files for input/output redirection based on file type.
 * Handles both input redirection (e.g., `<`)
 * and output redirection (e.g., `>` or `>>`).
 *
 * @param head Abstract Syntax Tree (AST) node containing file information.
 * @param pipe_state Structure managing pipe and redirection state.
 * @param env Environment variables and shell state.
 * @param status Current execution status.
 * @return Updated status after handling file operations.*/
int	open_file_for_redirection(t_ast_node *head, t_pipe_state *pipe_state,
	t_env *env, int status)
{
	if (head->file_type == READ_FILE || head->file_type == READ_FROM_APPEND)
		status = handle_input_redirection(head, pipe_state, env);
	else
		status = handle_output_redirection(head, pipe_state);
	return (status);
}

/** @brief Handles input redirection by opening
 * input files or processing heredocs.
 *
 * @param head AST node containing file type and arguments.
 * @param pipe_state Pipe state structure for managing redirection state.
 * @param env Environment variables and shell state.
 * @return 0 on success, -1 on failure (e.g., file not found).*/
int	handle_input_redirection(t_ast_node *head, t_pipe_state *pipe_state,
	t_env *env)
{
    (void)env;
	if (head->file_type == READ_FILE)
	{
		pipe_state->current_input_fd = open(head->args[0], O_RDONLY);
		pipe_state->has_input_file = (pipe_state->current_input_fd >= 0);
		if (!pipe_state->has_input_file)
			return (-1);
		return (0);
	}
	else if (head->file_type == READ_FROM_APPEND)
	{
		pipe_state->heredoc_status = exec_here_doc(head->args[0],
				pipe_state, env);
		signal(SIGINT, handle_ctrl_c);
		return (0);
	}
	return (0);
}

/** @brief Handles output redirection by opening files for writing or appending.
 *
 * @param head AST node containing file type and arguments.
 * @param pipe_state Pipe state structure for managing redirection state.
 * @return 0 on success, -1 on failure (e.g., permission denied).*/
int	handle_output_redirection(t_ast_node *head, t_pipe_state *pipe_state)
{
	int	mode;

	mode = O_TRUNC;
	if (head->file_type == WRITE_FILE_APPEND)
		mode = O_APPEND;
	pipe_state->current_output_fd = open(head->args[0],
			O_WRONLY | O_CREAT | mode, 0666);
	pipe_state->has_output_file = (pipe_state->current_output_fd >= 0);
	if (!pipe_state->has_output_file)
		return (-1);
	return (0);
}

/** @brief Executes piped commands by recursively processing AST nodes.
 * Manages pipes, redirections, and commands in a pipeline.
 *
 * @param head AST node representing the current command or redirection.
 * @param piped_state Structure tracking pipe and redirection state.
 * @param env Environment variables and shell state.
 * @param fd File descriptors for piping.
 * @return Execution status of the pipeline.*/
int	handle_piped_cmd_exec(t_ast_node *head, t_pipe_state *piped_state,
	t_env *env, int *fd)
{
	int	status;

	if (head->file_type == EXECUTE_FILE)
	{
		piped_state->is_redirection_or_pipe = 0;
		status = prepare_and_execute_cmd(head->args, fd, piped_state, env);
	}
	if (head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_OUT
		|| head->type == TOKEN_REDIR_APPEND
		|| head->type == TOKEN_REDIR_HEREDOC)
		return (handle_redirection_cmd(head, piped_state, env, fd));
	if (head->left)
		status = handle_piped_cmd_exec(head->left, piped_state, env, fd);
	if (head->right)
		status = handle_piped_cmd_exec(head->right, piped_state, env, fd);
	return (status);
}

/** @brief Handles redirection commands, updating pipe and file descriptors.
 * Manages redirection types (input, output, append, heredoc)
 * and executes commands if needed.
 *
 * @param head AST node representing the redirection.
 * @param piped_state Pipe state structure containing redirection information.
 * @param env Environment variables and shell state.
 * @param fd File descriptors for redirection.
 * @return Status after processing redirection. */
int	handle_redirection_cmd(t_ast_node *head, t_pipe_state *piped_state,
	t_env *env, int *fd)
{
	int	status;

	piped_state->second_heredoc_status = 1;
	if (head->right)
	{
		status = open_file_for_redirection(head->right, piped_state, env, 0);
		if ((status || !head->left) && piped_state->pipes_count > 1)
			piped_state->pipes_count -= 1;
	}
	if (head->left && head->left->file_type == EXECUTE_FILE
		&& piped_state->second_heredoc_status && !status)
	{
		piped_state->is_redirection_or_pipe = 1;
		status = prepare_and_execute_cmd(head->left->args,
				fd, piped_state, env);
	}
	if (head->left && head->left->type == TOKEN_PIPE
		&& piped_state->second_heredoc_status)
		status = handle_piped_cmd_exec(head->left, piped_state, env, fd);
	if (head->left && (head->left->type == TOKEN_REDIR_IN
			|| head->left->type == TOKEN_REDIR_OUT
			|| head->left->type == TOKEN_REDIR_APPEND
			|| head->left->type == TOKEN_REDIR_HEREDOC))
	{
		status = handle_redirection_cmd(head->left, piped_state, env, fd);
	}
	return (status);
}

/** @brief Executes an AST node by determining
 * its type and processing commands or redirections.
 * Manages pipe and file descriptor cleanup after execution.
 *
 * @param head AST node representing the current command or operation.
 * @param piped_state Pipe state structure containing execution state.
 * @param env Environment variables and shell state.
 * @return Final status after execution.*/
int	execute_ast_node(t_ast_node *head, t_pipe_state *piped_state, t_env *env)
{
	int	status;
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (head->type != TOKEN_WORD)
	{
		if (head->file_type == FILE_READY)
			status = handle_piped_cmd_exec(head, piped_state, env, fd);
		if (head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_OUT
			|| head->type == TOKEN_REDIR_APPEND
			|| head->type == TOKEN_REDIR_HEREDOC)
			status = handle_redirection_cmd(head, piped_state, env, fd);
	}
	if (head->file_type == EXECUTE_FILE)
		status = prepare_and_execute_cmd(head->args, fd, piped_state, env);
	status = wait_for_children(status, piped_state);
	if (piped_state->has_input_file)
		close(piped_state->current_input_fd);
	if (piped_state->has_output_file)
		close(piped_state->current_output_fd);
	if (fd[0] != -1 || fd[1] != -1)
		(close(fd[0]), close(fd[1]));
	return (g_signal = 0, status);
}

/** @brief Main entry point for executing commands in the AST.
 * Initializes pipe state, processes variables,
 * checks permissions, and executes commands.
 *
 * @param head AST node representing the root of the command structure.
 * @param env Environment variables and shell state.
 * @param status Pointer to store the final execution status.*/
void	command_executer(t_ast_node *head, t_env *env, int *status)
{
	t_pipe_state	piped_state;
	int				_status;

	init_or_reset_pipe_state(&piped_state, 1);
	count_redirect_and_pipes(head, &piped_state);
	init_or_reset_pipe_state(&piped_state, 0);
	adjust_ast_node_for_execution(head);
	//expand_vars_in_ast(head, env);
	_status = check_file_permissions(head, env->original_env);
	if (!_status)
		*status = execute_ast_node(head, &piped_state, env);
}
