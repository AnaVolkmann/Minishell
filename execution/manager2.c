/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:46:22 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/26 11:47:35 by ana-lda-         ###   ########.fr       */
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

	f_args = prepare_cmd_args(cmd[0], env->parsed_env, 0);
	cmd_args = merge_cmd_args(f_args, cmd);
 	if (command_is_builtin(cmd_args[0]))
		env->exit_status = (manage_builtin_execution(cmd_args, fd, env, piped));
    if (!piped->is_redirection_or_pipe)
    {
        piped->children_count += 1;
		env->exit_status = execute_basic_cmd(cmd_args, fd, env, piped);
		free_envp(cmd_args);
	}
	else
		env->exit_status = execute_cmd_with_redirect(cmd_args, fd,
					env, piped);
	if (piped->executed_pipes_index > 1)
		piped->executed_pipes_index -= 1;
	return (env->exit_status);
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
int open_file_for_redirection(t_ast_node *head, t_pipe_state *state, t_env *env, int status)
{
    int mode;

    if (head->file_type == READ_FILE)
    {
        switch_fds_identifier(state, 1, 1);  // Passa apenas a estrutura e o índice de entrada
        state->current_input_fd = open(head->args[0], O_RDONLY);
        if (state->current_input_fd < 0)
            status = switch_fds_identifier(state, 0, 0);  // Se falhar, volta ao estado original
    }
    else if (head->file_type == READ_FROM_APPEND)
    {
        switch_fds_identifier(state, 1, 1);  // Usamos apenas o índice de entrada
        status = exec_here_doc(head->args[0], state, env);
        signal(SIGINT, handle_ctrl_c);
    }
    else
    {
        switch_fds_identifier(state, 2, 1);  // Usamos o índice de saída
        mode = O_TRUNC;
        if (head->file_type == WRITE_FILE_APPEND)
            mode = O_APPEND;
        state->current_output_fd = open(head->args[0], O_WRONLY | O_CREAT | mode, 0666);
    }
    return status;
}

int switch_fds_identifier(t_pipe_state *state, int index, int con)
{
    if (con)
    {
        if (index == 1)  // Entrada
        {
            if (state->current_input_fd)
                close(state->current_output_fd); // Fecha o FD de saída se necessário
            state->current_input_fd = 1;  // Define o FD de entrada
        }
        else if (index == 2)  // Saída
        {
            if (state->current_output_fd)
                close(state->current_input_fd); // Fecha o FD de entrada se necessário
            state->current_output_fd = 1;  // Define o FD de saída
        }
    }
    else
    {
        ft_putendl_fd("err: file not found", 2);
        state->current_input_fd = 0;  // Reset de erro
    }
    return 1;
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
