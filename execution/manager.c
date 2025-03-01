/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:14:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/26 11:51:59 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Handles output redirection by opening files for writing or appending.
 *
 * @param head AST node containing file type and arguments.
 * @param pipe_state Pipe state structure for managing redirection state.
 * @return 0 on success, -1 on failure (e.g., permission denied).*/
int handle_output_redirection(t_ast_node *head, t_pipe_state *pipe_state)
{
    int mode;

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
int handle_piped_cmd_exec(t_ast_node *head, t_pipe_state *piped_state,
                          t_env *env, int *fd)
{
    if (head->file_type == EXECUTE_FILE)
    {
        piped_state->is_redirection_or_pipe = 0;
        env->exit_status = prepare_and_execute_cmd(head->args, fd, piped_state, env);
    }
    if (head->type == T_REDIR_IN || head->type == T_REDIR_OUT || head->type == T_REDIR_APPEND || head->type == T_REDIR_HEREDOC)
        return (handle_redirection_cmd(head, piped_state, env, fd));
    if (head->left)
        env->exit_status = handle_piped_cmd_exec(head->left, piped_state, env, fd);
    if (head->right)
        env->exit_status = handle_piped_cmd_exec(head->right, piped_state, env, fd);
    return (env->exit_status);
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
int handle_redirection_cmd(t_ast_node *head, t_pipe_state *piped_state,
                           t_env *env, int *fd)
{
    piped_state->second_heredoc_status = 1;
    if (head->right)
    {
        env->exit_status = open_file_for_redirection(head->right, piped_state, env, 0);
        if ((env->exit_status || !head->left) && piped_state->executed_pipes_index > 1)
            piped_state->executed_pipes_index -= 1;
    }
    if (head->left && head->left->file_type == EXECUTE_FILE && piped_state->second_heredoc_status && !env->exit_status)
    {
        piped_state->is_redirection_or_pipe = 1;
        env->exit_status = prepare_and_execute_cmd(head->left->args,
                                                   fd, piped_state, env);
    }
    if (head->left && head->left->type == T_PIPE && piped_state->second_heredoc_status)
        env->exit_status = handle_piped_cmd_exec(head->left, piped_state, env, fd);
    if (head->left && (head->left->type == T_REDIR_IN || head->left->type == T_REDIR_OUT || head->left->type == T_REDIR_APPEND || head->left->type == T_REDIR_HEREDOC))
        env->exit_status = handle_redirection_cmd(head->left, piped_state, env, fd);
    return (env->exit_status);
}

/** @brief Executes an AST node by determining
 * its type and processing commands or redirections.
 * Manages pipe and file descriptor cleanup after execution.
 *
 * @param head AST node representing the current command or operation.
 * @param piped_state Pipe state structure containing execution state.
 * @param env Environment variables and shell state.
 * @return Final status after execution.*/
int execute_ast_node(t_ast_node *head, t_pipe_state *piped_state, t_env *env)
{
    int fd[2];

    fd[0] = -1;
    fd[1] = -1;
    if (head->file_type == FILE_READY)
    {
        if (head->type == T_PIPE)
            env->exit_status = handle_piped_cmd_exec(head, piped_state, env, fd);
        if (head->type == T_REDIR_IN || head->type == T_REDIR_OUT || head->type == T_REDIR_APPEND || head->type == T_REDIR_HEREDOC)
            env->exit_status = handle_redirection_cmd(head, piped_state, env, fd);
    }
    if (head->file_type == EXECUTE_FILE)
        env->exit_status = prepare_and_execute_cmd(head->args, fd, piped_state, env);
    env->exit_status = wait_for_children(env->exit_status, piped_state);
    if (piped_state->has_input_file)
            close(piped_state->current_input_fd);
    if (piped_state->has_output_file)
        close(piped_state->current_output_fd);
    if (fd[0] != -1 || fd[1] != -1)
        (close(fd[0]), close(fd[1]));
    return (g_signal = 0, env->exit_status);
}

/** @brief Main entry point for executing commands in the AST.
 * Initializes pipe state, processes variables,
 * checks permissions, and executes commands.
 *
 * @param head AST node representing the root of the command structure.
 * @param env Environment variables and shell state.
 * @param status Pointer to store the final execution status.*/
void command_executer(t_ast_node *head, t_env *env, int *status)
{
    t_pipe_state piped_state;
    int _status;

    init_or_reset_pipe_state(&piped_state, 1);
    count_redirect_and_pipes(head, &piped_state);
    init_or_reset_pipe_state(&piped_state, 0);
    adjust_ast_node_for_execution(head);
    expand_vars_in_ast(head, env);
    _status = check_file_permissions(head, env->parsed_env);
    if (!_status)
    {
       if (head->left == NULL && head->right == NULL)
           execute(head->args[0], head->args, env, &piped_state.current_output_fd);
       else
            *status = execute_ast_node(head, &piped_state, env);
    }
}
