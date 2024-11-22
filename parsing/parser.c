/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:27:54 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/22 15:18:31 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int parse(t_token *token, t_shell *shell)
{
    //consider token[0] as the cmd
    //consider token[1+] as the argument until finding an operator
    //after operator check if the operation is "doable"
    //loop to the next block (right side of the operator)
}*/
/*
parse_tokens(*token)
parse_pipeline(*token) - handles pipes, calls redir for each side of the pipe
parse_redir(*tokens) - handles redir calls command nodes with the args
!!!each node represets either a command, a redir, our a pipeline
!!node_type!!!!

*/

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*command_node;
	int			arg_count;
	int			i;
	t_token		*temp;

	command_node = create_new_ast_node(TOKEN_WORD);
	arg_count = count_command_args(*token);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
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

t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*temp;
	t_token		*next_token;
	t_ast_node	*redirect_node;

	if (!*tokens)
		return (NULL);
	temp = *tokens;
	if ((*tokens)->type >= TOKEN_REDIR_IN && (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		return (build_redirection_node(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= TOKEN_REDIR_IN && (*tokens)->next->type <= TOKEN_REDIR_HEREDOC)
		{
			redirect_node = create_new_ast_node((*tokens)->next->type);
			(*tokens)->next = (*tokens)->next->next;
			redirect_node->left = parse_redirection(&temp);
			redirect_node->right = create_file_node(next_token->next);
			return (free(next_token), free(next_token->value), redirect_node);
		}
		*tokens = next_token;
	}
	return (parse_command(&temp));
}

t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_token		*temp;
	t_token		*next_token;
	t_ast_node	*pipe_node;

	temp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == TOKEN_PIPE)
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

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
