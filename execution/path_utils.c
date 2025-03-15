/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:31:12 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/03/15 14:31:15 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Checks if a path is accessible with the specified mode.
 *
 * @param path Path to the file or directory.
 * @param mode Accessibility check mode (e.g., `R_OK`, `W_OK`, `X_OK`).
 * @return Returns `1` if the path is accessible; otherwise, returns `0`.*/
int	is_path_accessible(char *path, int mode)
{
	if (access(path, mode) < 0)
		return (0);
	return (1);
}

/** @brief Verifies the path of a file without
 * referencing environment variables.
 *
 * @param file The file name or path to verify.
 * @param mode Accessibility check mode (e.g., `R_OK`, `W_OK`, `X_OK`).
 * @return Allocated string containing the verified path if accessible;
 * `NULL` otherwise.*/
char	*verify_path_without_env(char *file, int mode)
{
	char	*temp_path;
	int		i;

	i = sizeof_str(file, ' ');
	temp_path = malloc(i + 1);
	if (temp_path)
		return (NULL);
	ft_strcopy(temp_path, file, 0, i);
	if (is_path_accessible(temp_path, mode))
		return (temp_path);
	free(temp_path);
	return (NULL);
}

/** @brief Calculates the length of a string up to the specified end character.
 *
 * @param str Input string.
 * @param end Character where the count should stop.
 * @return Number of characters up to `end` or the end of the string.*/
int	sizeof_str(char *str, char end)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && str[i] != end)
		i++;
	return (i);
}

/** @brief Extracts the next substring from a string using
 * a delimiter, skipping quotes.
 *
 * @param str Input string to parse.
 * @param del Delimiter separating substrings.
 * @param index Pointer to the current parsing index.
 * @return Allocated string containing the next substring.*/
char	*find_next_substring(char *str, char del, int *index)
{
	char	*sub;
	int		size;
	int		i;

	while (str[index[0]] && str[index[0]] == del)
		index[0]++;
	size = sizeof_str(str + index[0], del);
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (str[index[0]] && str[index[0]] != del)
	{
		if (str[index[0]] != 34 && str[index[0]] != 39)
			sub[i++] = str[index[0]];
		index[0]++;
	}
	sub[i] = '\0';
	index[0]++;
	return (sub);
}

/** @brief Parses a command string into arguments and
 * resolves the command's executable path.
 *
 * @param cmd The command string to parse (e.g., `"ls -la"`).
 * @param envp Array of environment variables.
 * @param c Counter for parsed arguments.
 * @return Array of strings representing the parsed command and arguments.*/
char	**prepare_cmd_args(char *cmd, char **envp, int c)
{
	char	**parsed_cmd;
	char	*cmd_holder;
	int		index[3];

	index[1] = count_substrings(cmd, ' ');
	parsed_cmd = malloc(sizeof(char *) * (index[1] + 1));
	index[0] = 0;
	while (c < index[1])
	{
		cmd_holder = find_next_substring(cmd, '\0', index);
		if (!c && !command_is_builtin(cmd_holder))
		{
			parsed_cmd[c] = get_file_path(cmd_holder, envp, "PATH", X_OK);
			if (!parsed_cmd[c])
				parsed_cmd[c] = ft_strdup(cmd_holder);
			free(cmd_holder);
		}
		else
			parsed_cmd[c] = cmd_holder;
		if (!parsed_cmd[c])
			return (NULL);
		c += 1;
	}
	parsed_cmd[c] = NULL;
	return (parsed_cmd);
}
