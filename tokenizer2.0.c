/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:14 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/06 18:06:50 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *process_to_tokenize_input(char *input)
{
	char *trimmed_input;
	t_token *tokens;

	trimmed_input = ft_strtrim(input," \t\n\v\f\r");
	free(input);
	if (!trimmed_input)
		return (NULL);
	//if (syntax error)
	//	free(trimmed_input);
	tokens = tokenize_input(trimmed_input);/*(funcao que vai separar char especiais e palavras e outros tipos);*/
	free(trimmed_input);
	return (tokens);
}
/** @brief splits the input into tokens based on spaces, special characters, and words) */
t_token *tokenize_input(char *input)
{
	t_token *token;

	token = NULL;
	while(*input)
	{
		while(ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
		{
			handle_special_chars(input, token);
		}
		else
		{
			handle_word(input, token);
		}
	}
	return(token);
}
// (TODO)add_token_to_list
// (TODO)new_token
// (TODO)add_word_to_list
// (TODO)syntax_verification funtion
void	handle_special_chars(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			//add_token_to_list(tokens, new_token(TOKEN_REDIR_APPEND, ">>"));
			(*input)++;
		}
		else
			//add_token_to_list(tokens, new_token(TOKEN_REDIR_OUT, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			//add_token_to_list(tokens, new_token(TOKEN_REDIR_HEREDOC, "<<"));
			(*input)++;
		}
		else
			//add_token_to_list(tokens, new_token(TOKEN_REDIR_IN, "<"));
	}
	else if (**input == '|')
		add_token_to_list(tokens, new_token(TOKEN_PIPE, "|"));
	(*input)++;
}

void handle_word(char **input, t_token **tokens)
{
	char	*start;
	char	quote_char;
	int		in_quotes;

	start = *input;
	in_quotes = 0;
	quote_char = '\0';
	while(**input)
	{

	}
	// add word to list if token is valid;
}