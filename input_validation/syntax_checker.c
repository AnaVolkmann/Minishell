/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:39:19 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/08 15:49:19 by ana-lda-         ###   ########.fr       */
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
		ft_putstr_fd();
		return (1);
	}
	if (has_missalined_operator(input))
	{
		ft_putstr_fd();
		return (1);
	}
	if (has_logical_operators(input))
	{
		ft_putstr_fd("&&" "||");
		return (1);
	} */
	return (0);
}

int	has_unclosed_quotes(const char *input)
{
	char quote_type;

	quote_type = 0;
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