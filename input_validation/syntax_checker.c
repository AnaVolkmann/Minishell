/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:39:19 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/19 14:49:59 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Checks for syntax errors in the input string.
 * 
 * Validates the input string for common syntax errors, such
 * as unclosed quotes, 
 * invalid redirections, misplaced operators, and unsupported
 * logical operators.
 * @param input The input string to check.
 * @return 1 if a syntax error is found, 0 otherwise.*/
int	syntax_error_checker(const char *input)
{
	if (has_unclosed_quotes(input))
	{
		ft_putstr_fd("Syntax error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	if (has_invalid_redirections(input))
	{
		ft_putstr_fd("Syntax error: invalid redirection\n", STDERR_FILENO);
		return (1);
	}
	if (has_misplaced_operators(input))
	{
		ft_putstr_fd("Syntax error: misplaced operator\n", STDERR_FILENO);
		return (1);
	}
	if (has_logical_operators(input))
	{
		ft_putstr_fd("Error: Logical operators '&&' and '||' \
			are not supported.\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

/** @brief Checks if the input string contains unclosed quotes.
 * 
 * This function scans the input string to detect whether there are unclosed single
 * or double quotes. It toggles the state each time it encounters a quote character
 * (' or "), and if it finds an unmatched quote at the end of the string, it returns 1
 * (indicating an error). If all quotes are properly closed, it returns 0.
 * 
 * @param input The input string to check for unclosed quotes.
 * @return 1 if there are unclosed quotes, 0 if all quotes are properly closed.
 * @note This function does not handle escape sequences (e.g., `\'` or `\"`) within the string.*/
int	has_unclosed_quotes(const char *input)
{
	char quote_type;

	quote_type = 0;
	if (!input)
		return (0);
	while(*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			if (*input == quote_type)
				quote_type = 0;
			else if (!quote_type)
				quote_type = *input;
		}
		input++;
	}
	return (quote_type != 0);
}

/** @brief Checks for invalid redirections in the input string.
 * 
 * Scans for `>` or `<` redirection operators, ensuring they are used correctly
 * outside of quoted sections. Returns 1 if an invalid redirection is detected.
 * @param input The input string to check.
 * @return 1 if an invalid redirection is found, 0 otherwise.*/
int	has_invalid_redirections(const char *input)
{
	int	single_q_count;
	int	double_q_count;

	single_q_count = 0;
	double_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &single_q_count, &double_q_count);
		if ((!(single_q_count % 2) && !(double_q_count % 2))
			&& (*input == '>' || *input == '<'))
		{
			if (is_invalid_operator(&input))
				return (1);
		}
		else
			input++;
	}
	return (0);
}

/** @brief Checks for misplaced operators in the input string.
 * 
 * Detects operators (`|`, `&`) that are used incorrectly, such as at the start
 * of the string or when not followed by a command.
 * Returns 1 if a misplaced operator is found.
 * @param input The input string to check.
 * @return 1 if an operator is misplaced, 0 otherwise.*/
int	has_misplaced_operators(const char *input)
{
	int	expect_command_next;
	int	single_q_count;
	int	double_q_count;

	single_q_count = 0;
	double_q_count = 0;
	expect_command_next = 0;
	if (*input == '|' || *input == '&')
		return (1);
	while (*input)
	{
		update_quote_counts(*input, &single_q_count, &double_q_count);
		if (*input == '|' && !(single_q_count % 2) && !(double_q_count % 2))
		{
			if (expect_command_next)
				return (1);
			expect_command_next = 1;
		}
		else if (!ft_isspace(*input))
			expect_command_next = 0;
		input++;
	}
	if (expect_command_next)
		return (1);
	return (0);
}

/** @brief Checks for unsupported logical operators in the input string.
 * 
 * Detects logical operators (`&&`, `||`) in the input string
 * and returns 1 if any are found.
 * @param input The input string to check.
 * @return 1 if logical operators are found, 0 otherwise.*/
int	has_logical_operators(const char *input)
{
	int	single_q_count;
	int	double_q_count;

	single_q_count = 0;
	double_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &single_q_count, &double_q_count);
		if (!(double_q_count % 2) && !(single_q_count % 2)
			&& ((*input == '&' && *(input + 1) == '&')
				|| (*input == '|' && *(input + 1) == '|')))
			return (1);
		input++;
	}
	return (0);
}