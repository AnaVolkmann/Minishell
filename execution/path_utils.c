/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:17:54 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 13:41:19 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_next_substring(char *str, char del, int *index)
{
	char	*sub;
	int		size;
	int		i;

	while(str[index[0]] && str[index[0]] == del)
		index[0]++;
	//size = len de str + index[0];
	sub = malloc(size + 1);
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
		//cmd_holder = find_next_substring();
		if (!c && !command_is_builtin(cmd_holder))
		{
			//parsed_cmd = get_file_path(cmd_holder, envp, "PATH", X_OK);
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
