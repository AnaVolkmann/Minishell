/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:27:45 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/26 14:36:17 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Adjusts the file type of AST nodes for execution.
 * Assigns appropriate file types based on token type
 * (e.g., redirections, pipes).
 * Recursively processes left and right child nodes in the AST.
 *
 * @param head AST node representing a command, redirection, or pipe.*/
void	adjust_ast_node_for_execution(t_ast_node *head)
{
	if (head->type != T_WORD)
	{
		head->file_type = FILE_READY;
		if (head->type == T_REDIR_OUT && head->right)
			head->right->file_type = WRITE_FILE;
		if (head->type == T_REDIR_APPEND && head->right)
			head->right->file_type = WRITE_FILE_APPEND;
		if (head->type == T_REDIR_IN && head->right)
			head->right->file_type = READ_FILE;
		if (head->type == T_REDIR_HEREDOC && head->right)
			head->right->file_type = READ_FROM_APPEND;
		if (head->type == T_PIPE)
		{
			if (head->right)
				head->right->file_type = EXECUTE_FILE;
			if (head->left)
				head->left->file_type = EXECUTE_FILE;
		}
		if (!head->file_type)
			head->file_type = EXECUTE_FILE;
		if (head->left)
			adjust_ast_node_for_execution(head->left);
		if (head->right)
			adjust_ast_node_for_execution(head->right);
	}
}

/** @brief Finds the absolute path of an executable using environment variables.
 *
 * @param file The file name to locate.
 * @param envp Array of environment variables.
 * @param env_var The specific environment variable (e.g., `"PATH"`)
 * 				to search within.
 * @param mode Accessibility check mode (e.g., `R_OK`, `W_OK`, `X_OK`).
 * @return Allocated string containing the absolute path if found and
 * accessible; `NULL` otherwise.*/
/* char	*get_file_path(char *file, char **envp, char *env_var, int mode)
{
	char	*tmp_path;
	int		var_len;
	int		index;
	int		flag;

	flag = 0;
	var_len = sizeof_str(env_var, '\0');
	index = find_substr_index(envp, env_var, var_len);
	if (index < 0 || (file[0] == '.' && file[1] == '/'))
		return (verify_path_without_env(file, mode));
	if (sizeof_str(file, ' ') != sizeof_str(file, '\0')
		&& !is_path_accessible(file, mode))
		return (NULL);
	while (envp[index][var_len])
	{
		tmp_path = create_subpath_from_var(envp[index], file, var_len, &flag);
		if (!tmp_path)
			return (NULL);
		if (is_path_accessible(tmp_path, mode))
			return (tmp_path);
		free(tmp_path);
		if (!flag)
			flag = 1;
	}
	return (NULL);
} */

char	*get_file_path(char *file, char **envp, char *env_var, int mode)
{
	char				*tmp_path;
	int					indx_s[4];

	indx_s[3] = 0;
	indx_s[1] = sizeof_str(env_var, '\0');
	indx_s[0] = find_substr_index(envp, env_var, indx_s[1]);
	if (indx_s[0] < 0
		|| (file[0] && file[1] && file[0] == '.' && file[1] == '/'))
		return (verify_path_without_env(file, mode));
	indx_s[2] = sizeof_str(envp[indx_s[0]], '\0');
	if (sizeof_str(file, ' ') != sizeof_str(file, '\0')
		&& !is_path_accessible(file, mode))
		return (NULL);
	while (envp[indx_s[0]][indx_s[1]])
	{
		tmp_path = create_subpath_from_var(envp[indx_s[0]], file, indx_s);
		if (!tmp_path)
			return (NULL);
		if (is_path_accessible(tmp_path, mode))
			return (tmp_path);
		free(tmp_path);
		if (!indx_s[3])
			indx_s[3] = 1;
	}
	return (NULL);
}

/** @brief Checks file permissions for commands and redirection files.
 * Validates access rights for executable commands or
 * files used in input/output redirection.
 * Reports errors and updates the shell's exit status
 * if permission issues are detected.
 *
 * @param head AST node containing the command or file to check.
 * @param env Environment variables, used to resolve paths.
 * @return 1 if an error is detected, 0 otherwise.*/
int	check_file_permissions(t_ast_node *head, char **env)
{
	int		status;
	char	*path;

	status = 0;
	if (head->args && !command_is_builtin(head->args[0])
		&& head->file_type == READ_FILE)
	{
		path = get_file_path(head->args[0], env, "PWD", R_OK);
		if (!path)
			status = 0;
		else
		{
			is_sus_dir(path, head->args[0], &status);
			free(path);
		}
		status = specify_error(head->args[0], status);
	}
	if (!status && head->left)
		status = check_file_permissions(head->left, env);
	if (!status && head->right)
		status = check_file_permissions(head->right, env);
	return (status);
}

int	specify_error(char *file, int _status)
{
	if (_status == 1)
	{
		_status = get_shell_exit_status(errno);
		ft_putstr_fd("   err: \'", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\' ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (_status);
	}
	else if (_status)
	{
		ft_putstr_fd("   minishell(\'", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd("\'): permission denied", 2);
	}
	return (_status);
}

/** @brief Counts the number of redirections and pipes in the AST.
 * Updates the `t_pipe_state` structure with counts of
 * input/output files and pipe segments.
 * Processes the AST recursively to include all child nodes.
 *
 * @param head AST node representing the command structure.
 * @param piped_state Structure to store counts of pipes and redirections.*/
void	count_redirect_and_pipes(t_ast_node *head, t_pipe_state *piped_state)
{
	head->file_type = 0;
	if (head->type == T_REDIR_OUT || head->type == T_REDIR_APPEND)
		piped_state->output_files_count += 1;
	else if (head->type == T_REDIR_IN || head->type == T_REDIR_HEREDOC)
		piped_state->input_files_count += 1;
	else if (head->type == T_PIPE)
		piped_state->pipes_count += 1;
	if (head->left)
		count_redirect_and_pipes(head->left, piped_state);
	if (head->right)
		count_redirect_and_pipes(head->right, piped_state);
}

int	count_strings_in_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}

int	is_string_numeric(char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!ft_isdigit(s1[i]))
			return (0);
		i++;
	}
	return (1);
}