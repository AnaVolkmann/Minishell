/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:07:48 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int key_len(char *path)
{
    int i;

    i = 0;
    while (path[i] && path[i] != '=')
        i++;
    return (i);
}

int export(char *path, char **envp)
{
    int     len;
    int     i;
    char    *exp;

    i = 0;
    len = key_len(path);
    if (path[len] != '=')
        return (printf("Export: invalid format: use KEY=VALUE\n"), -1);
    exp = ft_strdup(path);
    if (exp == NULL)
        return (printf("Error: memory allocation failed: %s.\n", strerror(errno)), -1);
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], path, len) == 0 && envp[i][len] == '=')
        {
            free(envp[i]);
            envp[i] = exp;
            return (0);
        }
        i++;
    }
    envp[i] = exp;
    envp[i + 1] = NULL;
    return (0);
}
