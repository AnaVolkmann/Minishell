/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:15:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/01 14:11:16 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_token(t_token **token_list, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*tmp;
	
	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (new_token->value == NULL)
		return (free(new_token), NULL);
	new_token->next = NULL;
	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		tmp = *token_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (new_token);
}

void	free_token_list(t_token **token_list)
{
	t_token	*tmp;
	t_token	*next;
	
	tmp = *token_list;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*token_list = NULL;
}
