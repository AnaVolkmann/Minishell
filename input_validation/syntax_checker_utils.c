/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:24:17 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/18 17:12:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Updates quote counters based on the given character.
 * Increments the single or double quote counters when a
 *  quote character (`'` or `"`) is encountered.
 * @param c The current character.
 * @param single_q_count Pointer to the single quote counter.
 * @param double_q_count Pointer to the double quote counter.*/
void	update_quote_counts(char c, int *single_q_count, int *double_q_count)
{
	if (c == 34)
		(*double_q_count)++;
	else if (c == 39)
		(*single_q_count)++;
}

/** @brief Skips leading whitespace characters in the input string.
 * Iterates through the string, skipping spaces and tabs,
 *  and returns a pointer to the first non-whitespace character.
 * @param input The input string.
 * @return A pointer to the first non-whitespace character.*/
const char	*skip_spaces(const char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

/** @brief Checks if the current operator is invalid.
 * Validates if the operator is followed by invalid characters
 * (like `>`, `<`, `|`), indicating a syntax error.
 * @param input Pointer to the operator in the input string.
 * @return 1 if the operator is invalid, 0 otherwise.*/
int	is_invalid_operator(const char **input)
{
	const char	*operator_start;

	operator_start = *input;
	(*input)++;
	if (*operator_start == **input)
		(*input)++;
	*input = skip_spaces(*input);
	if (**input == '\0' || **input == '>'
		|| **input == '<' || **input == '|')
		return (1);
	return (0);
}
