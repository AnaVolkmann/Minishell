/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:19:58 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/03/13 18:12:56 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Counts the number of arguments in a command.
 *
 * This function counts the number of consecutive tokens of type `TOKEN_WORD`,
 * representing the
 * arguments of a command. It traverses the token list starting from the
 * current token.
 *
 * @param current A pointer to the token list to be parsed.
 * @return The number of command arguments (tokens of type `TOKEN_WORD`).*/
int	count_command_args(t_token *current)
{
	int	i;

	i = 0;
	while (current && current->type == T_WORD)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/** @brief Creates a new AST node with the specified token type.
 *
 * This function allocates memory for a new AST node, initializes its type,
 * and sets its left,
 * right, and args fields to NULL. The node represents a generic AST element
 * with a specific type.
 *
 * @param type The type of the token that this node will represent.
 * @return A pointer to the newly created AST node,
 * or NULL if memory allocation fails.*/
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

/** @brief Creates an AST node representing a file, linked to a given token.
 *
 * This function creates an AST node to represent a file associated with
 * the given token. The file
 * node is allocated with space for a single argument (the file name) and
 * sets the node's left and
 * right child pointers to NULL.
 *
 * @param token The token representing the file to be used in the AST node.
 * @return A pointer to the created file AST node,
 * or NULL if memory allocation fails.*/
// t_ast_node	*create_file_node(t_token *token)
// {
// 	t_ast_node	*file_node;

// 	file_node = malloc(sizeof(t_ast_node));
// 	if (!file_node)
// 		return (NULL);
// 	file_node->type = token->type;
// 	file_node->args = malloc(sizeof(char *) * 2);
// 	if (!file_node->args)
// 	{
// 		free (file_node);
// 		return (NULL);
// 	}
// 	file_node->args[0] = token->value;
// 	file_node->args[1] = NULL;
// 	file_node->left = NULL;
// 	file_node->right = NULL;
// 	return (file_node);
// }
t_ast_node	*create_file_node(t_token *token)
{
	t_ast_node	*file_node;

	file_node = create_new_ast_node(token->type);
	if (!file_node)
		return (NULL);
	file_node->args = malloc(sizeof(char *) * 2);
	if (!file_node->args)
		return (free(file_node), NULL);
	file_node->args[0] = token->value;
	file_node->args[1] = NULL;
	return (file_node);
}

/** @brief Creates and links an AST node for redirection.
 *
 * This function creates a redirection node by first
 * creating a new AST node for the current
 * redirection token, then parsing the left side (redirection details)
 * and linking the right side
 * (the file node). It consumes tokens in the process.
 *
 * @param tokens A pointer to the token list to be parsed.
 * @param tmp A temporary token used to link the redirection file.
 * @return A pointer to the newly created redirection AST node.*/
t_ast_node	*build_redirection_node(t_token **tokens, t_token *tmp)
{
	t_ast_node	*redirect_node;

	redirect_node = create_new_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	//redirect_node->left = parse_command(&tmp);
	redirect_node->left = parse_redirection(tokens);
	redirect_node->right = create_file_node(tmp->next);
	free(tmp->value);
	free(tmp);
	return (redirect_node);
}

// é preciso dar free no que retornar da expansion()
// e se a expansao estiver no meio do node?
/* t_ast_node	*expand_vars_in_ast(t_ast_node *ast, t_env *env)
{
	char	*expanded;

	if (!ast)
		return (NULL);
	if (ast->args && ast->args[0])
	{
		expanded = expansion(ast->args[0], env->shell, env);
		if (expanded)
		{
			free (ast->args[0]);
			ast->args[0] = ft_strdup(expanded);
			free (expanded);
		}
	}
	if (ast->left)
		expand_vars_in_ast(ast->left, env);
	if (ast->right)
		expand_vars_in_ast(ast->right, env);
	return (ast);
}
 */
