/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:27:54 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/03/12 11:55:56 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Parses a command and creates a corresponding AST node.
 *
 * processes the tokens representing a command and creates an AST node to
 * represent
 * the command, including its arguments. It dynamically allocates memory
 * for the arguments and
 * populates them from the tokens. The tokens are consumed in the process.
 *
 * @param token A pointer to the token list to be parsed.
 * @return A pointer to the created AST node, or NULL if memory allocation
 * fails.*/
t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*command_node;
	int			arg_count;
	int			i;
	t_token		*temp;

	command_node = create_new_ast_node(T_WORD);
	arg_count = count_command_args(*token);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (free(command_node), NULL);
	i = 0;
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*token)->value);
		temp = *token;
		*token = (*token)->next;
		free(temp->value);
		free(temp);
		i++;
	}
	command_node->args[arg_count] = NULL;
	return (command_node);
}

/** @brief Parses redirection tokens and creates a redirection AST node.
 *
 * This function processes redirection tokens, builds an AST node to represent
 * the redirection,
 * and links the corresponding left and right child nodes. The redirection
 * can be one of several
 * types (e.g., input, output, or heredoc). It also consumes tokens in the
 * process.
 *
 * @param tokens A pointer to the token list to be parsed.
 * @return A pointer to the created redirection AST node, or NULL if
 * no redirection is found.*/
t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*temp;
	t_token		*file_token;
	t_ast_node	*redirect_node;

	temp = *tokens;
	if ((*tokens)->type >= T_REDIR_IN && (*tokens)->type <= T_REDIR_HEREDOC)
		return (build_redirection_node(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		if ((*tokens)->next->type >= T_REDIR_IN
			&& (*tokens)->next->type <= T_REDIR_HEREDOC)
		{
			file_token = (*tokens)->next->next;
			if (!file_token)
				return (printf("Error: redirection with no file specified.\n"), NULL);
			redirect_node = create_new_ast_node((*tokens)->next->type);
			(*tokens)->next = file_token->next;
			redirect_node->left = parse_redirection(tokens); // preciso ver o que fazer em caso de multiplos redirects
			//redirect_node->left = parse_command(&temp);
			redirect_node->right = create_file_node(file_token);
			return (redirect_node);
		}
		*tokens = (*tokens)->next;
	}
	return (parse_command(&temp));
}

/** @brief Parses redirection tokens and creates a redirection AST node.
 *
 * This function processes redirection tokens, builds an AST node
 * to represent the redirection,
 * and links the corresponding left and right child nodes.
 * The redirection can be one of several
 * types (e.g., input, output, or heredoc).
 * It also consumes tokens in the process.
 *
 * @param tokens A pointer to the token list to be parsed.
 * @return A pointer to the created redirection AST node, or NULL if
 * no redirection is found.*/
t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_token		*temp;
	t_token		*next_token;
	t_ast_node	*pipe_node;

	temp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == T_PIPE)
		{
			pipe_node = create_new_ast_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = parse_redirection(&temp);
			pipe_node->right = parse_pipeline(&(next_token->next));
			free(next_token->value);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (parse_redirection(&temp));
}

/** @brief Parses a list of tokens and creates the root AST node.
 *
 * This function is responsible for initiating the
 * parsing process by calling the appropriate
 * parsing functions (pipeline, redirection, command) and
 * building the AST from the provided tokens.
 *
 * @param tokens A pointer to the token list to be parsed.
 * @return A pointer to the root of the AST, or
 * NULL if the token list is empty or invalid.*/
t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
