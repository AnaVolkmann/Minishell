/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:46:22 by lufiguei          #+#    #+#             */
/*   Updated: 2025/03/15 14:09:31 by ana-lda-         ###   ########.fr       */
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
	else if (!piped->is_redirection_or_pipe)
	{
		piped->children_count += 1;
		env->exit_status = execute_basic_cmd(cmd_args, fd, env, piped);
	}
	else
		env->exit_status = execute_cmd_with_redirect(cmd_args, fd,
					env, piped);
	if (piped->executed_pipes_index > 1)
		piped->executed_pipes_index -= 1;
	if (cmd_args)
		free_envp(cmd_args);
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
/* int	open_file_for_redirection(
	t_ast_node *head, t_pipe_state *piped, t_env *env, int status)
{
	int			mode;

	if (head->file_type == READ_FILE)
	{
		switch_fds_identifier(piped, 6, 1, 1);
		piped->current_input_fd = open(head->args[0], O_RDONLY);
		if (piped->current_input_fd < 0)
			status = switch_fds_identifier(piped, 0, 0, 0);
	}
	else if (head->file_type == READ_FROM_APPEND)
	{
		switch_fds_identifier(piped, 6, 1, 1);
		status = exec_here_doc(head->args[0], piped, env);
		signal(SIGINT, handle_ctrl_c);
	}
	else
	{
		switch_fds_identifier(piped, 7, 2, 1);
		mode = O_TRUNC;
		if (head->file_type == WRITE_FILE_APPEND)
			mode = O_APPEND;
		piped->current_output_fd = open(head->args[0], O_WRONLY | O_CREAT | mode, 0666);
	}
	return (status);
} */
int open_file_for_redirection(
    t_ast_node *head, t_pipe_state *piped, t_env *env, int status)
{
    int mode;

    // Redirecionamento de leitura (input)
    if (head->file_type == READ_FILE)  // "< arquivo"
    {
        switch_fds_identifier(piped, 6, piped->current_input_fd, 1);
        piped->current_input_fd = open(head->args[0], O_RDONLY);
        if (piped->current_input_fd < 0)
        {
            perror("Error opening file for input redirection");
            status = switch_fds_identifier(piped, 0, 0, 0);
        }
    }
    // Here-doc (<<)
    else if (head->file_type == READ_FROM_APPEND)  // "<< limiter"
    {
        switch_fds_identifier(piped, 6, piped->current_input_fd, 1);
        status = exec_here_doc(head->args[0], piped, env);  // Chama o heredoc
        signal(SIGINT, handle_ctrl_c);
    }
    // Redirecionamento de escrita (>)
    else if (head->file_type == WRITE_FILE || head->file_type == WRITE_FILE_APPEND)
    {
        if (head->args[0] == NULL) {
            fprintf(stderr, "Error: Output file path is NULL.\n");
            return -1;
        }

        printf("Attempting to open file: %s\n", head->args[0]);
        switch_fds_identifier(piped, 7, piped->current_output_fd, 1);

        // Definindo o modo de abertura (modo de sobrescrição ou append)
        mode = O_TRUNC;
        if (head->file_type == WRITE_FILE_APPEND)  // Se for ">>"
            mode = O_APPEND;

        // Abre o arquivo com as permissões apropriadas
        piped->current_output_fd = open(head->args[0], O_WRONLY | O_CREAT | mode, 0666);
        if (piped->current_output_fd < 0) {
            perror("Error opening file for output redirection");
            return -1;
        }

        printf("File opened successfully: %s\n", head->args[0]);
        printf("Redirecting output to file...\n");

        // Redireciona a saída para o arquivo
        // Imprimir antes e depois do redirecionamento
        printf("Antes do redirecionamento: current_output_fd = %d\n", piped->current_output_fd);
        if (dup2(piped->current_output_fd, STDOUT_FILENO) < 0) {
            perror("Erro ao redirecionar saída para o arquivo");
            return -1;
        }
        printf("Após o dup2: stdout foi redirecionado para o arquivo.\n");
        // Verificar se o arquivo foi criado e tem conteúdo após a execução do comando
        printf("Verificando conteúdo de 'a':\n");
        system("cat a");
    }
    return status;
}



int switch_fds_identifier(t_pipe_state *piped, int index, int fd_to_close, int con)
{
    if (con)
    {
        if (index == 6)  // Se for input file ("<") ou heredoc ("<<")
        {
            if (piped->has_input_file && piped->current_input_fd > 0)
                close(piped->current_input_fd);  // Fecha o FD antigo

            piped->has_input_file = 1;
            piped->current_input_fd = fd_to_close;  // Atualiza com o FD do heredoc
        }
        else if (index == 7)  // Se for output file (">" ou ">>")
        {
            if (piped->has_output_file && piped->current_output_fd > 0)
                close(piped->current_output_fd);

            piped->has_output_file = 1;
            piped->current_output_fd = fd_to_close;
        }
    }
    else
    {
        ft_putendl_fd("Erro: arquivo não encontrado", 2);
        if (index == 6)
            piped->has_input_file = 0;
        else if (index == 7)
            piped->has_output_file = 0;
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
