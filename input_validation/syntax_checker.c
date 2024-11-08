/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:39:19 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/08 17:09:43 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error_checker(const char *input)
{
	if (has_unclosed_quotes(input))
	{
		ft_putstr_fd("Syntax error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	/* if (has_invalid_redirec(input))
	{
		ft_putstr_fd("Syntax error: invalid redirection\n", STDERR_FILENO);
		return (1);
	}
	if (has_missalined_operator(input))
	{
		ft_putstr_fd("Syntax error: misplaced operator\n", STDERR_FILENO);
		return (1);
	}
	if (has_logical_operators(input))
	{
		ft_putstr_fd("&&" "||");
		return (1);
	} */
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
 * 
 * @return 1 if there are unclosed quotes, 0 if all quotes are properly closed.
 * 
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

/* int	has_invalid_redirect(const char *input)
{
	int	single_q_count;
	int	double_q_count;

	single_q_count = 0;
	double_q_count = 0;
	while(*input)
	{
		//update_quote_count
		
	}
} */