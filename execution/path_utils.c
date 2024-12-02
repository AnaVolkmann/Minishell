/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:17:54 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 14:49:29 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path_accessible(char *path, int mode)
{
	if (access(path, mode) < 0)
		return (0);
	return (1);
}
char	*verify_path_without_env(char *file, int mode)
{
	char	*temp_path;
	int		i;

	i = sizeof_str(file, ' ');
	temp_path = malloc(i + 1);
	if (temp_path)
		return (NULL);
	ft_strcopy(temp_path, file, 0, i);
	if (is_path_accessible(temp_path, mode))
		return (temp_path);
	free(temp_path);
	return (NULL);
}

// locate the executable file's absolute path by:
char	get_file_path(char *file, char **envp, char *env_var, int mode)
{
	char	*temp_path;
	int		env_var_len;
	int		env_var_index;
	int		env_value_len;
	int		flag;

	flag = 0;
	env_var_len = sizeof_str(env_var, '\0');
	env_var_index = find_substr_index(envp, env_var, env_var_len);
	if (env_var_index < 0 || file[0] == '.' && file[1] == '/')
		return (verify_path_without_env(file, mode));
	env_value_len = sizeof_str(envp[env_var_index], '\0');
	if (sizeof_str(file, ' ') != sizeof_st(file, '\0') && !is_path_accessible(file, mode))
		return (NULL);
	while (envp[env_var_index][env_var_len])
	{
		temp_path = create_subpath_from_var(envp[env_var_index], file, &env_var_len, &flag);
		if (!temp_path)
			return NULL;
		if (is_path_accessible(temp_path, mode))
			return (temp_path);
		free(temp_path);
		if (!flag)
			flag = 1;
	}
	return NULL;
}

int	sizeof_str(char *str, char end)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && str[i] != end)
		i++;
	return (i);
}

char	*find_next_substring(char *str, char del, int *index)
{
	char	*sub;
	int		size;
	int		i;

	while(str[index[0]] && str[index[0]] == del)
		index[0]++;
	size = sizeof_str(str + index[0], del);
	if (!sub)
		return (NULL);
	i = 0;
	while(str[index[0]] && str[index[0]] != del)
	{
		if (str[index[0]] != 34 && str[index[0]] != 39)
			sub[i++] = str[index[0]];
		index[0]++;
	}
	sub[i] = '\0';
	index[0]++;
	return(sub);
}
/** Parse a command string (cmd) into individual arguments. */
char **prepare_cmd_args(char *cmd, char **envp, int c)
{
	char	**parsed_cmd;
	char	*cmd_holder;
	int		index[3];

	index[1] = count_substring(cmd, ' ');
	parsed_cmd = malloc(sizeof(char *) * (index[1] + 1));
	index[0] = 0;
	while(c < index[1])
	{
		cmd_holder = find_next_substring(cmd, '\0', index);
		if (!c && !command_is_builtin(cmd_holder))
		{
			parsed_cmd = get_file_path(cmd_holder, envp, "PATH", X_OK);
			if (!parsed_cmd)
				parsed_cmd = ft_strdup(cmd_holder);
			free(cmd_holder);
		}
		else
			parsed_cmd[c] = cmd_holder;
		if (!parsed_cmd)
			return (NULL);
	}
	parsed_cmd[c] = NULL;
	return (parsed_cmd);
}
