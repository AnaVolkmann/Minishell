/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:27:45 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/27 17:19:18 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	adjust_ast_node_for_execution(t_ast_node *head)
{
	if (head->type != TOKEN_WORD)
	{
		head->file_type = FILE_READY;
		if (head->type == TOKEN_REDIR_OUT && head->right)
			head->right->file_type = WRITE_FILE;
		if (head->type == TOKEN_REDIR_APPEND && head->right)
			head->right->file_type = WRITE_FILE_APPEND;
		if (head->type == TOKEN_REDIR_IN && head->right)
			head->right->file_type = READ_FILE;
		if (head->type == TOKEN_REDIR_HEREDOC && head->right)
			head->right->file_type = READ_FROM_APPEND;
		if (head->type == TOKEN_PIPE)
		{
			if (head->right)
				head->right->file_type = EXECUTE_FILE;
			if (head->left)
				head->left->file_type = EXECUTE_FILE;
		}
		if (!head->file_type)
			head->file_type = EXECUTE_FILE;
		if (!head->left)
			adjust_ast_node_for_execution(head->left);
		if (head->right)
			adjust_ast_node_for_execution(head->right);
	}
}
//TODO ------- SUS_PATH, GET PATH
int	check_file_permissions(t_ast_node *head, char **env)
{
	int		status;
	char	*path;

	status = 0;
	if (head->args && !check_if_cmd_is_builtin(head->args[0]) && head->file_type == READ_FILE)
	{
		path = get_path(head->args[0], env, "PWD", R_OK);
		if (!path)
			status = 0;
		else
		{
			//suspicious path (is_susp_dir(path, head->args[0], &status);
			free(path);
		}
		if (status == 1)
		{
			ft_putstr_fd("   err: \'", 2);
			ft_putstr_fd(head->args[0], 2);
			ft_putstr_fd("\' ", 2);
			ft_putendl_fd(strerror(errno), 2);
			update_exit(get_shell_exit_status(errno), head->shell);
		}
		else if (status)
		{
			ft_putstr_fd("   minishell(\'", 2);
			ft_putstr_fd(head->args[0], 2);
			ft_putendl_fd("\'): permission denied", 2);
			update_exit(1, head->shell);
		}
	}
	if (!status && head->left)
		status = check_file_permissions(head->left, env);
	if (!status && head->right)
		status = check_file_permissions(head->right, status);
	return (status);
}

void	count_redirect_and_pipes(t_ast_node *head, t_pipe_state *piped_state)
{
	head->file_type = 0;

	if (head->type == TOKEN_REDIR_OUT || TOKEN_REDIR_APPEND)
		piped_state->output_files_count += 1;
	else if (head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_HEREDOC)
		piped_state->input_files_count += 1;
	else if (head->type == TOKEN_PIPE)
		piped_state->pipes_count += 1;
	if (head->left)
		count_redirect_and_pipes(head->left, piped_state);
	if (head->right)
		count_redirect_and_pipes(head->right, piped_state);
}