/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:15:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 16:25:37 by ana-lda-         ###   ########.fr       */
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

int	token_to_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		printf("TOKEN_WORD");
	else if (type == TOKEN_PIPE)
		printf("TOKEN_PIPE");
	else if (type == TOKEN_REDIR_IN)
		printf("TOKEN_REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		printf("TOKEN_REDIR_OUT");
	else if (type == TOKEN_REDIR_APPEND)
		printf("TOKEN_REDIR_APPEND");
	else if (type == TOKEN_REDIR_HEREDOC)
		printf("TOKEN_REDIR_HEREDOC");
	else if (type == TOKEN_ENV_VAR)
		printf("TOKEN_ENV_VAR");
	else if (type == TOKEN_COMMAND)
		printf("TOKEN_COMAND");
	else if (type == TOKEN_RULE)
		printf("TOKEN_RULE");
	else if (type == TOKEN_QUOTE)
		printf("TOKEN_QUOTE");
}

/*t_token	**tokenizer(char *line)
{
	int		i;
	char	*start;
	char	*value;
	t_token	**token_list;

	token_list = malloc(sizeof(t_token *));
	if (token_list == NULL)
		return (printf("Error: Memory allocation for token list.\n"), NULL);
	*token_list = NULL;
	while (*line)
	{
		i = 0;
		if (*line == ' ' || (*line <= 13 && *line >= 9))
			line++;
		if (*line >= 'a' && *line <= 'z')
		{
			start = line;
			while (*line >= 'a' && *line <= 'z')
			{
				line++;
				i++;
			}
			value = malloc(sizeof(char) * (i + 1));
			if (value == NULL)
				return (printf("Error: Memory allocation CMD.\n"), free_token_list(token_list), NULL);
			ft_strlcpy(value, start, i + 1);
			if (!append_token(token_list, COMMAND, value))
					return (printf("Error: Memory allocation CMD.\n"), free_token_list(token_list), NULL);
			free (value);
		}
		if (*line == '-')
		{
			start = line;
			line++;
			i++;
			if (*line >= 'a' && *line <= 'z')
			{
				while (*line >= 'a' && *line <= 'z')
				{
					line++;
					i++;
				}
				value = malloc(sizeof(char) * (i + 1));
				if (value == NULL)
					return (printf("Error: Memory allocation RULE.\n"), free_token_list(token_list), NULL);
				ft_strlcpy(value, start, i + 1);
				if (!append_token(token_list, RULE, value))
					return (printf("Error: Memory allocation RULE.\n"), free_token_list(token_list), NULL);
				free (value);
			}
		}
		if (*line == '$')
		{
			start = line;
			line++;
			i++;
			while (*line && (ft_isalnum(*line) || *line == '_'))
			{
				line++;
				i++;
			}
			value = malloc(sizeof(char) * (i + 1));
			if (value == NULL)
				return (printf("Error: Memory allocation ENV_VAR.\n"), free_token_list(token_list), NULL);
			ft_strlcpy(value, start, i + 1);
			if (!append_token(token_list, TOKEN_ENV_VAR, value))
				return (printf("Error: Memory allocation ENV_VAR.\n"), free_token_list(token_list), NULL);
			free (value);
		}
		if (*line == '|' || *line == '<' || *line == '>')
		{	else if (type == TOKEN_PIPE)
		printf("TOKEN_PIPE");
			value = malloc(sizeof(char) * 2);
			if (value == NULL)
				return (printf("Error: Memory allocation OPERATOR.\n"), free_token_list(token_list), NULL);
			ft_strlcpy(value, line, 2);
			if (!append_token(token_list, OPERATOR, value))
				return (printf("Error: Memory allocation OPERATOR.\n"), free_token_list(token_list), NULL);
			free (value);
		}
		if (*line == 34 || *line == 39)
		{
			value = malloc(sizeof(char) * 2);
			if (value == NULL)
				return (printf("Error: Memory allocation QUOTE.\n"), free_token_list(token_list), NULL);
			ft_strlcpy(value, line, 2);
			if (!append_token(token_list, QUOTE, value))
				return (printf("Error: Memory allocation QUOTE.\n"), free_token_list(token_list), NULL);
			free (value);
			line++;
			// chamar recursiva? tokenizer(line);
		}
		else
		{
			start = line;
			line++;
			i++;
			while (*line && (*line != '$' && *line != 34 && *line != 39
					&& *line != '|' && *line != '<' && *line != '>'))
			value = malloc(sizeof(char) * (i + 1));
			if (value == NULL)
				return (printf("Error: Memory allocation WORD.\n"), free_token_list(token_list), NULL);
			ft_strlcpy(value, line, i + 1);
			if (!append_token(token_list, WORD, value))
				return (printf("Error: Memory allocation WORD.\n"), free_token_list(token_list), NULL);
			free (value);
		}
		line++;
	}
	return (token_list);
}*/
