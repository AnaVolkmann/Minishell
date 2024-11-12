#include "minishell.h"

void    free_envp(char **envp)
{
    int i;

    if (!envp)
        return ;
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

void    free_shell(t_shell *shell)
{
    if (!shell)
        return ;
    if (shell->envp)
        free_envp(shell->envp);
    // if (shell->input)
    //     free(shell->input);
    // if (shell->path)
    //     free(shell->path);
}
