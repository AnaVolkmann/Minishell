/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:27:54 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/20 14:00:07 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

typedef struct		s_ast_node
{
	t_token_type	type;
	char			**args;
	struct			s_ast_node *left;
	struct			s_ast_node *right;
	int				file_type;//indicates the type of redirection(input, output, append), if no redirec, set to 0.
}					t_ast_node;

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}