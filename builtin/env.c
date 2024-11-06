/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:55:50 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/06 12:34:30 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief searching for an environment  variable in the provided
 *  environment array and returning its value.
 * This function takes the name of an environment variable and an array of environment 
 * variables, and returns the value of the variable if found.
 * @param var   The name of the environment variable to search for.
 * @param envp  The array of environment variables (e.g., `environ`).
 * 
 * @return A string containing the value of the environment variable,
 *  or NULL if the variable is not found.*/
char *get_env(char *var, char **envp)
{
	int i;
	int var_len;
	int eq_pos;

	if (!var || !envp)
		return NULL;
	var_len = ft_strlen(var);
	i = 0;
	while (envp[i]) 
	{
		eq_pos = ft_strchr_i(envp[i], '=');
		if (eq_pos != -1 && !ft_strncmp(envp[i], var, var_len) && envp[i][var_len] == '=')
			return ft_substr(envp[i], eq_pos + 1, ft_strlen(envp[i]) - eq_pos - 1);
		i++;
	}
	return NULL;
}

/* int main()
{
    char *envp[] = 
	{
        "USER=alice",
        "HOME=/home/alice",
        "PATH=/usr/bin:/bin:/usr/sbin:/sbin",
        "SHELL=/bin/bash",
        NULL // NULL-terminated array of strings
    };
    char *result = get_env("USER", envp);
    if (result)
	{
        printf("USER: %s\n", result);  // Expected output: "alice"
        free(result);
    }
	else
        printf("USER not found\n");
    result = get_env("HOME", envp);
    if (result)
	{
        printf("HOME: %s\n", result);  // Expected output: "/home/alice"
        free(result);
    }
	else
        printf("HOME not found\n");
    result = get_env("SHELL", envp);
    if (result)
	{
        printf("SHELL: %s\n", result);  // Expected output: "/bin/bash"
        free(result);
    }
	else
        printf("SHELL not found\n");
    result = get_env("NOT_EXIST", envp);
   	if (result)
   {
    printf("NOT_EXIST: %s\n", result);
    free(result);
	}
 else 
    printf("NOT_EXIST not found\n");
    return 0;
} */
