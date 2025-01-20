/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:27:45 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/04 17:06:27 by ana-lda-         ###   ########.fr       */
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
char	*get_file_path(char *file, char **envp, char *env_var, int mode)
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
		tmp_path = create_subpath_from_var(envp[index],	file, var_len, &flag);
		if (!tmp_path)
			return (NULL);
		if (is_path_accessible(tmp_path, mode))
			return (tmp_path);
		free(tmp_path);
		if (!flag)
			flag = 1;
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
		if (path)
		{
			is_sus_dir(path, head->args[0], &status);
			free(path);
			status = specify_error(head->args[0], status);
		}
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
	if (head->type == TOKEN_REDIR_OUT || head->type == TOKEN_REDIR_APPEND)
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
