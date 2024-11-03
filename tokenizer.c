/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:15:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/01 13:17:10 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*append_token(t_token **token_list, t_token_type type, char *value)
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

static void	free_token_list(t_token **token_list)
{
	t_token	*tmp;
	t_token	*next;
	
	tmp = *token_list;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*token_list = NULL;
}

t_token	**tokenizer(char *line)
{
	int	i;
	t_token **token_list;

	i = 0;
	*token_list = NULL;
	while (line[i])
	{
		if (line[i] == 32)
			i++;
		else if (line[i] == '-')
			if (!append_token(*token_list, RULE, line[i++]))
				return (printf(stderr, "Error: Memory allocation.\n"), free_token_list(*token_list), NULL);
		else if (line[i] == '$')
			append_token(*token_list, ENV_VAR, line[i++]);
		else if (islower(line[i]) == 1)
			append_token(*token_list, COMMAND, line[i++]);
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			append_token(*token_list, OPERATOR, line[i++]);
		else if (line[i] == 34 || line[i] == 39)
			append_token(*token_list, QUOTE, line[i++]);
		else
			append_token(*token_list, WORD, line[i++]);
	}
}
