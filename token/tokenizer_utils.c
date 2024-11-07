/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:11:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/07 14:06:57 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Adds a new token to the end of the token list.
 * 
 * This function appends a new token to the end of a linked list of tokens. 
 * If the list is empty, the new token becomes the head of the list.
 *
 * @param tokens A pointer to the head of the token list.
 * @param new_token The token to be added to the list.*/
void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token *last;

	if(!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while(last->next)
			last = last->next;
		last->next = new_token;
	}
}

/**
 * @brief Creates a new token with the specified type and value.
 * 
 * This function allocates memory for a new token, sets its type and value, 
 * and initializes its `next` pointer to NULL. If memory allocation fails, 
 * it returns NULL.
 *
 * @param type The type of the new token (e.g., TOKEN_WORD, TOKEN_REDIR_IN, etc.).
 * @param value The string value associated with the token.
 *
 * @return A pointer to the newly created token, or NULL if memory allocation fails.*/
t_token	*new_token(t_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

/**
 * @brief Adds a word token to the token list.
 * 
 * This function creates a token of type `TOKEN_WORD` from the substring 
 * between `start` and `input` pointers, and adds it to the token list.
 * If the memory allocation for the word fails, it prints an error message.
 *
 * @param start A pointer to the beginning of the word to be tokenized.
 * @param input A pointer to the current position in the input string.
 * @param tokens A pointer to the head of the token list.*/
void	add_word_token(char **start, char **input, t_token **tokens)
{
	char *word;

	if (*input > *start)
	{
		word = ft_strndup(*start, (*input - *start));
		if (word)
		{
			add_token_to_list(tokens, new_token(TOKEN_WORD, word));
			//free(word);
		}
		else
			ft_putstr_fd("Error: Malloc failed in handle_word.\n", 2);
	}
}

/**
 * @brief Frees the memory allocated for the token list.
 * 
 * This function iterates through the token list, freeing the memory for 
 * each token's value and the token structure itself. After calling this 
 * function, the token list should no longer be used.
 *
 * @param tokens The head of the token list to be freed.*/
void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

/**
 * @brief Updates the quote status based on the current character.
 * 
 * This function tracks whether the input is inside a quote (either single 
 * or double quotes). If the character matches the current quote type, 
 * it toggles the `in_quote` status. Otherwise, it sets the quote character 
 * when the `in_quote` status is not active.
 *
 * @param c The current character being processed.
 * @param in_quote A pointer to an integer that tracks whether we are inside quotes.
 * @param quote_char A pointer to the character that indicates the current quote type (single or double).*/
void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}