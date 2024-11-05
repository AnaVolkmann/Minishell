// duplicate the environ variable so i can change it freely without screwin something else
// environ works as KEY=VALUE
// look up for the value you want, if you find it, delete, if not, all good
// the delete works as in a swap, you overwrite the one you want to "delete", 
// and shift everything else on top of it

#include "minishell.h"

int unset(char *path)
{
    int len;
    int i;
    int j;

    len = ft_strlen(path);
    i = 0;
    while (environ[i] != NULL)
    {
        if (ft_strncmp(environ[i], path, len) == 0 && environ[i][len] == '=')
        {
            free (environ[i]);
            j = i;
            while (environ[j] != NULL)
            {
                environ[j] = environ[j + 1];
                j++;
            }
            environ[j - 1] = NULL;
            return (0);
        }
        i++;
    }
    return (-1);
}
