#include "../minishell.h"

/**
 * @brief Replaces a substring (variable) in the string with a new value.
 *
 * Creates a new string by combining parts of the old string and the replacement value.*/
char	*replace_var_with_value(char *old_val, char *new_val, int start, int end)
{
	int		size;
	char	*new_str;
	int		new_size;

	new_size = sizeof_str(new_val, '\0');
	size = start + (sizeof_str(old_val, '\0') - end) + new_size;
	new_str = malloc(size + 1);
	if (!new_str)
		return (NULL);
	s_strcopy(new_str, old_val, 0, start);
	s_strcopy(new_str + start, new_val, 0, new_size);
	s_strcopy(new_str + start + new_size, old_val, end, sizeof_str(old_val, '\0'));
	free(old_val);
	return (new_str);
}

/**
 * @brief Checks if a character in the string can be the start of a valid variable.
 *
 * Determines if the character at the given index can start a variable, considering alphanumeric characters, underscores, and `?`.*/
int	is_valid_var_start(char *str, int index, int control)
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

/**
 * @brief Expands variables in the given string by replacing them with their values.
 *
 * Scans the string for variables (starting with `$`), retrieves their values from the environment, and replaces them in the string.*/
char *expand_vars_in_string(char *str, t_env *env, int start, int *expand_idx)
{
    int var_length;
    int idx;
    int end;
    char *var_name;

    end = start + 1;
    while (str[end] && is_valid_var_start(str, end, 0))
        end++;
    var_length = end - start;
    var_name = malloc(var_length + 1);
    s_strcopy(var_name, str, start + 1, end);
    if (str_cmp(var_name, "?", NULL) && g_signal)
        //update_env_status(env, g_signal, "?=");
	g_signal = 0;
    idx = find_env_var_index(env, var_name);
    free(var_name);
    *expand_idx = 0;
    if (idx >= 0)
    {
        var_name = replace_var_with_value(str, env->parsed_env[idx], start, end);
        *expand_idx = sizeof_str(env->parsed_env[idx], '\0') + start;
    }
    else
        var_name = replace_var_with_value(str, "", start, end);
    return (var_name);
}

/**
 * @brief Recursively expands variables in a string, handling nested variables and quotes.
 *
 * Expands variables in the string, considering nested variable expansions and quoted parts of the string.*/
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
		if (is_valid_var_start(var, array[0], 1)
			&& ((!(array[2] % 2) && control) || (array[2] % 2 && control)))
			return (new_var = expand_vars_in_string(var, env, array[0], &array[0]),
				recursively_expand_vars(new_var, env, control, array));
		array[0]++;
	}
	return (var);
}

/**
 * @brief Refactors an array of argument strings to handle syntax flaws.
 *
 * Processes the argument array to correct syntax issues, such as improper whitespace handling.*/
char	**refactor_args_array(char **args, int *sintax_fix)
{
	int						a;
	int						b;
	int						c;
	char					**new_args;

	a = 0;
	b = 0;
	*sintax_fix = 0;
	c = count_strings_in_array(args);
	new_args = malloc((count_total_flaws(args) + c + 1) * sizeof(char **));
	if (!new_args)
		return (NULL);
	while (args[a])
	{
		c = count_whitespace_flaws(args[a], 0, 0, 0);
		if (c)
			b = simple_refactor(new_args, b, args[a], 0);
		else
			new_args[b++] = strcopy(args[a]);
		a++;
	}
	new_args[b] = 0;
	free_envp(args);
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
			head->args[i] = remove_quotes_from_str(head->args[i], 0, 0, 0); // free?
			i++;
		}
	}
	if (head->left)
		expand_vars_in_ast(head->left, env);
	if (head->right)
		expand_vars_in_ast(head->right, env);
}
