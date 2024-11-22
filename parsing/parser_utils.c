/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:19:58 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/22 15:19:43 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_command_args(t_token *current)
{
	int	i;

	i = 0;
	while (current && current->type == TOKEN_WORD)
	{
		i++;
		current = current->next;
	}
	return (i);
}

t_ast_node	*create_new_ast_node(t_token_type type)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->args = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

t_ast_node	*create_file_node(t_token *token)
{
	t_ast_node	*file_node;

	file_node = malloc(sizeof(t_ast_node));
	if (!file_node)
		return (NULL);
	file_node->type = token->type;
	file_node->args = malloc(sizeof(char *) * 2);
	if (!file_node->args)
	{
		free(file_node);
		return (NULL);
	}
	file_node->args[0] = token->value;
	file_node->args[1] = NULL;
	file_node->left = NULL;
	file_node->right = NULL;
	free(token);
	return (file_node);
}

t_ast_node *create_and_link_redirection(t_token **tokens, t_token *tmp)
{
	t_ast_node	*redirect_node;

	redirect_node = new_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = parse_redirection(tokens);
	redirect_node->right = create_file_node(tmp->next);
	free(tmp->value);
	free(tmp);
	return (redirect_node);
}
