/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsett.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:07:08 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:07:17 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// duplicate the envp variable so i can change it freely without screwin something else
// envp works as KEY=VALUE
// look up for the value you want, if you find it, delete, if not, all good
// the delete works as in a swap, you overwrite the one you want to "delete", 
// and shift everything else on top of it

#include "../minishell.h"

int unset(char *path, char **envp)
{
    int len;
    int i;
    int j;

    len = ft_strlen(path);
    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], path, len) == 0 && envp[i][len] == '=')
        {
            free (envp[i]);
            j = i;
            while (envp[j] != NULL)
            {
                envp[j] = envp[j + 1];
                j++;
            }
            envp[j - 1] = NULL;
            return (0);
        }
        i++;
    }
    return (-1);
}
