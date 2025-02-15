/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:14 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/08 14:38:25 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Processes input string by trimming whitespace and tokenizing it.
 * 
 * This function trims leading and trailing whitespace characters from the
 * input string and then tokenizes it into meaningful chunks (e.g., words, 
 * special characters) by calling the `tokenize_input` function.
 *
 * @param input The input string to be processed and tokenized.
 *
 * @return A linked list of tokens representing the tokenized input, or NULL
 *         if memory allocation fails or if the input is empty.*/
t_token	*process_to_tokenize_input(char *input)
{
	char	*trimmed_input;
	t_token	*tokens;

	trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed_input)
		return (NULL);
	if (syntax_error_checker(trimmed_input))
	{
		free(trimmed_input);
		return (NULL);
	}
	tokens = tokenize_input(trimmed_input);
	free(trimmed_input);
	return (tokens);
}

/**
 * @brief Tokenizes an input string into individual tokens based on delimiters.
 * 
 * This function parses the input string and splits it into tokens. It handles
 * special characters (`<`, `>`, `|`) and words. It calls the appropriate
 * handler functions for different types of tokens.
 *
 * @param input The input string to be tokenized.
 *
 * @return A linked list of tokens representing the tokenized input.*/
t_token	*tokenize_input(char *input)
{
	t_token	*token;

	token = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
			handle_special_chars(&input, &token);
		else
			handle_word(&input, &token);
	}
	return (token);
}

/**
 * @brief Handles special characters in the input string and 
 * adds tokens for them.
 * 
 * This function checks for special characters (`>`, `<`, `|`) and processes
 * them accordingly. It creates tokens for redirect operators
 *  (`>`, `>>`, `<`, `<<`)
 * and pipes (`|`), then adds them to the token list.
 *
 * @param input A pointer to the current position in the input string.
 * @param tokens A pointer to the token list where new tokens are added.*/
void	handle_special_chars(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			add_token_to_list(tokens, new_token(T_REDIR_APPEND, ">>"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(T_REDIR_OUT, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			add_token_to_list(tokens, new_token(T_REDIR_HEREDOC, "<<"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(T_REDIR_IN, "<"));
	}
	else if (**input == '|')
		add_token_to_list(tokens, new_token(T_PIPE, "|"));
	(*input)++;
}

/**
 * @brief Processes a word in the input string and adds it as a token.
 * 
 * This function processes a word in the input string, which may be surrounded
 * by quotes, and adds it as a token to the token list. It also handles
 * quote characters (single or double quotes).
 *
 * @param input A pointer to the current position in the input string.
 * @param tokens A pointer to the token list where the word token is added.*/
void	handle_word(char **input, t_token **tokens)
{
	char	*start;
	char	quote_char;
	int		in_quotes;

	start = *input;
	in_quotes = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quotes, &quote_char);
		if (!in_quotes && ft_strchr(" \t\n><", **input))
			break ;
		(*input)++;
	}
	add_word_token(&start, input, tokens);
}
