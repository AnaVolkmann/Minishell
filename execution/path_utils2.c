/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:21:01 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/26 14:41:56 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increment_path_index(char *env_var, int *indx_s, int *a)
{
	if (indx_s[3])
	{
		indx_s[1] += 1;
		*a = indx_s[1];
		while (env_var[indx_s[1]] != '\0'
			&& env_var[indx_s[1]] != ':')
			indx_s[1] += 1;
	}
	else
		*a = indx_s[1];
}

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
char	*create_subpath_from_var(char *env_var, char *file, int *indx_s)
{
	char		*tmp_path;
	int			a;
	int			b;
	int			file_size;

	increment_path_index(env_var, indx_s, &a);
	file_size = sizeof_str(file, ' ');
	tmp_path = malloc((indx_s[1] - a) + file_size + 2);
	if (!tmp_path)
		return (NULL);
	b = 0;
	while (b < ((indx_s[1] - a) + file_size + 1))
	{
		if (indx_s[3] && (b < indx_s[1] - a))
			tmp_path[b] = env_var[a + b];
		else if (indx_s[3]
			&& env_var[indx_s[1] - 1] != '/'
			&& (b == indx_s[1] - a))
			tmp_path[b] = '/';
		else
			tmp_path[b] = file[b - (indx_s[1] - a) - indx_s[3]];
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
	while (str && str[i]) // valores nao inicializados?
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
