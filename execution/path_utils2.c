/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:21:01 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/03 11:46:48 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Combines an environment variable and file path into a new path.
 * 
 * Concatenates the environment variable and file, optionally adding a slash 
 * between them based on the flag.
 *
 * @param env_var Base environment variable.
 * @param file File path to append.
 * @param env_var_len Length of the environment variable.
 * @param flag Flag to control slash addition.
 * @return A new path string or NULL if allocation fails.*/
char	*create_subpath_from_var(char *env_var, char *file,
			int env_var_len, int *flag)
{
	char	*tmp_path;
	int		start_index;
	int		b;
	int		file_size;
	int		env_var_index;

	b = 0;
	start_index = 0;
	env_var_index = env_var_len;
	file_size = sizeof_str(file, ' ');
	tmp_path = malloc(env_var_index + file_size + 2);
	if (!tmp_path)
		return (NULL);
	while (b < (env_var_index + file_size + 1))
	{
		if (*flag && b < env_var_index)
			tmp_path[b] = env_var[start_index + b];
		else if (*flag && env_var[env_var_len - 1] != '/' && b == env_var_index)
			tmp_path[b] = '/';
		else
			tmp_path[b] = file[b - env_var_index - *flag];
		b++;
	}
	tmp_path[b] = '\0';
	return (tmp_path);
}

/** @brief Counts the number of substrings separated by a delimiter.
 * 
 * Traverses the string and counts substrings 
 * separated by the specified delimiter.
 *
 * @param str The input string.
 * @param del The delimiter character.
 * @return Number of substrings.*/
int	count_substrings(char *str, char del)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 1;
	result = 0;
	while (str[i] && str)
	{
		if (str[i] != del)
		{
			if (j)
				result++;
			j = 0;
		}
		else
			j = 1;
		i++;
	}
	return (result);
}

/** @brief Finds the index of a substring in an array of strings.
 * 
 * Searches for a substring in an array and
 * returns the index of the matching string.
 *
 * @param str Array of strings.
 * @param sub_str The substring to find.
 * @param n The length of the substring.
 * @return Index of the substring or -1 if not found.*/
int	find_substr_index(char **str, char *sub_str, int n)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == sub_str[0])
		{
			j = 0;
			while (str[i][j] && str[i][j] == sub_str[j])
			{
				if (j == (n -1))
					return (i);
				j++;
			}
		}
		i++;
	}
	return (-1);
}
