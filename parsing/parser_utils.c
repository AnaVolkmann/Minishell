/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:19:58 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/02/12 13:43:28 by alawrence        ###   ########.fr       */
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
		free (file_node);
		return (NULL);
	}
	file_node->args[0] = token->value;
	file_node->args[1] = NULL;
	file_node->left = NULL;
	file_node->right = NULL;
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
	*tokens = (*tokens)->next;
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
int	valid_var_start(char *str, int index, int control)
{
	if ((control && str[index] == '$'
			&& str[index + 1]
			&& str[index + 1] != '$'
			&& !ft_isspace(str[index + 1])
			&& (ft_isalnum(str[index + 1])
				|| str[index + 1] == '_'
				|| str[index + 1] == '?'))
		|| (!control && str[index]
			&& str[index] != '$'
			&& !ft_isspace(str[index])
			&& (ft_isalnum(str[index])
				|| str[index] == '_'
				|| str[index] == '?')))
		return (1);
	return (0);
}

char *expand_vars_in_string(char *str, t_env *env, int start, int *expand_idx)
{
    int var_length;
    int idx;
    int end;
    char *var_name;

    end = start + 1;
    while (str[end] && valid_var_start(str, end, 0))
        end++;
    var_length = end - start;
    var_name = malloc(var_length + 1);
    //s_strcopy(var_name, str, start + 1, end);
    if (str_cmp(var_name, "?", NULL) && g_signal)
        //update_env_status(env, g_signal, "?=");
	g_signal = 0;
   // idx = find_env_var_index(env, var_name);
    free(var_name);
    *expand_idx = 0;
    if (idx >= 0)
    {
        var_name = replace_var_with_value(str, env->parsed_env[idx][1], start, end);
        *expand_idx = sizeof_str(env->parsed_env[idx][1], '\0') + start;
    }
    else
        var_name = replace_var_with_value(str, "", start, end);
    return (var_name);
}

 char	*recursively_expand_vars(char *var, t_env *env, int control, int *array)
{
	char	*new_var;

	while (var[array[0]])
	{
		if (var[array[0]] == 39)
		{
			array[0]++;
			array[1]++;
			while (!(array[2] % 2) && var[array[0]] && var[array[0]] != 39)
				array[0]++;
		}
		if (var[array[0]] == 34)
			array[2]++;
		if (valid_var_start(var, array[0], 1)
			&& ((!(array[2] % 2) && control) || (array[2] % 2 && control)))
			return (new_var = expand_var_in_string(var, env, array[0], &array[0]),
				recursively_expand_vars(new_var, env, control, array));
		array[0]++;
	}
	return (var);
}

char	**refactor_args_array(char **args, int *norm_fix)
{
	int						a;
	int						b;
	int						c;
	char					**new_args;

	a = 0;
	b = 0;
	*norm_fix = 0;
	//c = count_strings_in_array(args);
	//new_args = malloc((detected_flaws(args) + c + 1) * sizeof(char **));
	if (!new_args)
		return (NULL);
	while (args[a])
	{
	//	c = flawed_str(args[a], 0, 0, 0);
		if (c)
	//		b = simple_refactor(new_args, b, args[a], 0);
		else
			new_args[b++] = strcopy(args[a]);
		a++;
	}
	new_args[b] = 0;
	//free_string_array(args);
	return (new_args);
}

/**
 * @brief Expands environment variables in the arguments of an AST node.
 *
 * This function recursively traverses the abstract syntax tree (AST) and expands any
 * environment variables (e.g., $HOME, $USER) in the arguments of each node. It performs
 * a two-phase expansion process, first expanding variables in the arguments, then
 * refactoring the argument array and removing any surrounding quotes from the expanded
 * strings. The function handles different argument types and ensures that all child
 * nodes (left and right) are processed recursively.
 *
 * @param head A pointer to the current AST node to be processed.
 * @param env A pointer to the environment structure containing variable mappings.
 *
 * @return The processed AST node with expanded variables in its arguments.*/
void	expand_vars_in_ast(t_ast_node *head, t_env *env)
{
	int	i;
	int	array[3];

	if (head->file_type != FILE_READY && head->args && head->file_type != READ_FROM_APPEND)
	{
		i = -1;
		while (head->args[++i])
		((ft_memset(array, 0, 3 * sizeof(int))),
		(head->args[i] = recursively_expand_vars(head->args[i], env, 1, array)));
		head->args = refactor_args_array(head->args, &i);
		while (head->args[i])
		{
			ft_memset(array, 0, 3 * sizeof(int));
			head->args[i] = recursively_expand_vars(head->args[i], env, 0, array);
			//head->args[i] = remove_quotes_from_str(head->args[i], 0, 0, 0);
			i++;
		}
	}
	if (head->left)
		expand_vars_in_ast(head->left, env);
	if (head->right)
		expand_vars_in_ast(head->right, env);
}