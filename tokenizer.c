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
	char **split;

	i = 0;
	split = ft_split(line, ' ');
	*token_list = NULL;
	if (split == NULL)
		return (NULL);
	while (split[i])
	{
		if (split[i][0] == '-')
			if (!append_token(*token_list, RULE, split[i++]))
				return (printf(stderr, "Error: Memory allocation.\n"), free_token_list(*token_list), NULL);
		else if (split[i][0] == '$')
			append_token(*token_list, ENV_VAR, split[i++]);
		else if (islower(split[i][0]) == 1)
			append_token(*token_list, COMMAND, split[i++]);
		else if (split[i][0] == '|' || split[i][0] == '<' || split[i][0] == '>')
			append_token(*token_list, OPERATOR, split[i++]);
		else if (split[i][0] == 34 || split[i][0] == 39)
			append_token(*token_list, QUOTE, split[i++]);
		else
			append_token(*token_list, WORD, split[i++]);
	}

}
