/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:24:01 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/12 19:10:49 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** @brief Compares two strings and optionally compares
 * with a third string.
 *
 * @param s_1 The first string to compare.
 * @param s_2 The second string to compare.
 * @param s_3 An optional third string to compare with the
 * first string if provided.
 * @return 1 if the first and second strings match in length and
 * content, or if the first and third strings match; 0 if the
 *  strings do not match.*/
int	str_cmp(char *s_1, char *s_2, char *s_3)
{
	int					a;

	a = 0;
	while (s_1[a] && s_2[a] && s_1[a] == s_2[a])
		a += 1;
	if (a == sizeof_str(s_1, '\0')
		&& a == sizeof_str(s_2, '\0'))
		return (1);
	if (s_3)
		return (str_cmp(s_1, s_3, NULL));
	return (0);
}

/** @brief Checks if the input string is empty, a newline,
 *  or only contains spaces.
 *
 * This function checks if the given input string is either empty,
 * a newline (`\n`),
 * or contains only whitespace characters. If any of these
 * conditions are true,
 * it frees the memory allocated to the input string and returns 1.
 * Otherwise, it returns 0.
 *
 * @param input A pointer to the input string to be checked.
 * @return 1 if the input is empty, a newline,
 *  or only spaces; 0 otherwise.*/
int	check_line(char **input)
{
	if (*input[0] == '\0' || ft_strcompare(*input, "\n", '\0')
		|| is_space(*input))
	{
		free(*input);
		return (1);
	}
	return (0);
}

char	*remove_quotes_from_str(char *str, int si_q_c, int do_q_c, int a)
{
	char				*new_str;
	int					b;

	b = 0;
	new_str = malloc(sizeof_str(str, '\0') + 1);
	while (str[a])
	{
		if (str[a] == 34 && !(si_q_c % 2))
			do_q_c++;
		else if (str[a] == 39 && !(do_q_c % 2))
			si_q_c++;
		if ((str[a] != 34 || si_q_c % 2)
			&& ((str[a] != 39) || do_q_c % 2))
			new_str[b++] = str[a];
		a++;
	}
	new_str[b] = '\0';
	return (free(str), new_str);
}

void	s_strcopy(char *s1, char *s2, int start, int end)
{
	int				i;

	i = 0;
	while (start < end)
		s1[i++] = s2[start++];
	s1[i] = '\0';
}

int	find_env_var_index(t_env *env, char *name)
{
	int		i;

	i = 0;
	while (env->parsed_env[i] != 0)
	{
		if (str_cmp(env->parsed_env[i], name, NULL))
			return (i);
		i++;
	}
	return (-1);
}