/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:14:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 12:11:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO - prepare_cmd_args
// merge_cmd;
// builtin_execution;
// execute_basic_cmd;
// comand_is_builtin
// execute_with_redirect;
// expand_vars_in_ast
// FINISH FUNCTION chech_file_permission

int	prepare_and_execute_cmd(char **cmd, int *fd, t_pipe_state *piped, t_env *env)
{
	char	**cmd_args;
	char	**f_args;
	int		status;

	//f_args = prepare_cmd_args(cmd[0], env->original_env, 0);
	//cmd_args = merge_cmd(f_args, cmd);
	if (command_is_builtin(cmd_args[0]))
		//status = builtin_execution;
	else
	{
		piped->children_count += 1;
		if (!piped->is_redirection_or_pipe)
		{
			//status = execute_basic_cmd();
			//free_array();
		}
		else
			//status = execute_cmd_with_redirect;
	if (piped->executed_pipes_index > 1)
		piped->executed_pipes_index -= 1;
	return (status);
	}

}

int open_file_for_redirection(t_ast_node *head, t_pipe_state *pipe_state, t_env *env, int status)
{
	if (head->file_type == READ_FILE || head->file_type == READ_FROM_APPEND)
		status = handle_input_redirection(head, pipe_state, env);
	else
		status = handle_output_redirection(head, pipe_state);

	return status;
}

int handle_input_redirection(t_ast_node *head, t_pipe_state *pipe_state, t_env *env)
{
	if (head->file_type == READ_FILE) // Input redirection
	{
		pipe_state->current_input_fd = open(head->args[0], O_RDONLY);
		pipe_state->has_input_file = (pipe_state->current_input_fd >= 0);
		return pipe_state->has_input_file ? 0 : -1; // Return success or error
	}
	else if (head->file_type == READ_FROM_APPEND) // Heredoc
	{
		pipe_state->heredoc_status = exec_here_doc(head->args[0], pipe_state, env);
		signal(SIGINT, handle_ctrl_c);
		return 0; // Assume heredoc is processed successfully
	}
	return 0;
}

int handle_output_redirection(t_ast_node *head, t_pipe_state *pipe_state)
{
	int mode = O_TRUNC;

	if (head->file_type == WRITE_FILE_APPEND)
		mode = O_APPEND;
	pipe_state->current_output_fd = open(head->args[0], O_WRONLY | O_CREAT | mode, 0666);
	pipe_state->has_output_file = (pipe_state->current_output_fd >= 0);
	return pipe_state->has_output_file ? 0 : -1; // Return success or error
}


int handle_piped_cmd_exec(t_ast_node *head, t_pipe_state *piped_state, t_env *env, int *fd)
{
	int	status;

	if (head->file_type == EXECUTE_FILE)
	{
		piped_state->is_redirection_or_pipe = 0;
		status = prepare_and_execute_cmd(head->args, fd, piped_state, env);
	}
	if (head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_OUT
		|| head->type == TOKEN_REDIR_APPEND || head->type == TOKEN_REDIR_HEREDOC)
		return (handle_redirection_cmd(head, piped_state, env, fd));
	if (head->left)
		status = handle_piped_cmd_exec(head->left, piped_state, env, fd);
	if (head->right)
		status = handle_piped_cmd_exec(head->right, piped_state, env, fd);
	return status;
}

int handle_redirection_cmd(t_ast_node *head, t_pipe_state *piped_state, t_env *env, int *fd)
{
	int status;

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
		status = prepare_and_execute_cmd(head->left->args, fd, piped_state, env);
	}
	if (head->left && head->left->type == TOKEN_PIPE
		&& piped_state->second_heredoc_status)
		status = handle_piped_cmd_exec(head->left, piped_state, env, fd);
	if (head->left && (head->left->type == TOKEN_REDIR_IN || head->left->type == TOKEN_REDIR_OUT
			|| head->left->type == TOKEN_REDIR_APPEND || head->left->type == TOKEN_REDIR_HEREDOC))
	{
		status = handle_redirection_cmd(head->left, piped_state, env, fd);
	}
	return status;
}

int	execute_ast_node(t_ast_node *head, t_pipe_state *piped_state, t_env *env)
{
	int	status;
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (head->type != TOKEN_WORD)
	{
		if (head->file_type = FILE_READY)
			status = handle_piped_cmd_exec(head, piped_state, env, fd);
		if (head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_OUT
		|| head->type == TOKEN_REDIR_APPEND || head->type == TOKEN_REDIR_HEREDOC)
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

void	command_executer(t_ast_node *head, t_env *env, int *status)
{
	t_pipe_state	piped_state;
	int				_status;

	init_or_reset_pipe_state(&piped_state, 1);
	count_redirect_and_pipes(head, &piped_state);
	init_or_reset_pipe_state(&piped_state, 0);
	adjust_ast_node_for_execution(head);
	expand_vars_in_ast(head, env);
	_status = check_file_permissions(head, env->original_env);
	if (!_status)
		*status = execute_ast_node(head, &piped_state, env);
}
