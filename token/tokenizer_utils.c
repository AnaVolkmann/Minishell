/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:11:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/07 13:49:15 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

/** @brief this funtion adds a new node to the end of the list */
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

/** @brief this funtion creates  anew token to add to the list with its specifications filled */
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