/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:18:13 by lufiguei          #+#    #+#             */
/*   Updated: 2025/03/15 13:48:32 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_builtin_and_exit(char **cmd_args, t_env *env, int *fd_out)
{
    env->exit_status = run_command_builtin(cmd_args, env, fd_out);
    free_envp(cmd_args);                           // testando
    cleanup_and_exit_shell(env, env->exit_status); // testando
    exit(WEXITSTATUS(env->exit_status));
}

int run_child_with_redirs(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped)
{
    pid_t pid;
    int fd_out[2];

    fd_out[1] = 1;
    if (piped->is_redirection_or_pipe && piped->has_output_file)
        fd_out[1] = piped->current_output_fd;
    if (piped->executed_pipes_index > 1 && (!piped->is_redirection_or_pipe || !piped->has_output_file))
        pipe(fd_out);
    pid = fork();
    if (!pid)
        exec_builtin_and_exit(cmd_args, env, fd_out);
    if (piped->is_redirection_or_pipe && piped->has_output_file)
    {
        safe_close(fd_out[1]);
        piped->has_output_file = 0;
    }
    if (!piped->has_input_file && !piped->has_output_file)
        piped->is_redirection_or_pipe = 0;
    if (piped->executed_pipes_index > 1 && (!piped->is_redirection_or_pipe || !piped->has_input_file))
    {
        safe_close(fd_out[1]);
        fd[0] = fd_out[0];
    }
    return (1);
}

int run_builtin_child(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped)
{
    pid_t pid;
    int fd_s[2];
    int fd_out[2];

    fd_s[0] = -1;
    fd_s[1] = -1;
    fd_out[1] = -1;
    if (pipe(fd_s) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (!pid)
    {
        if (piped->executed_pipes_index && piped->executed_pipes_index <= piped->pipes_count)
            if (fd[0] > 0)
                dup2(fd[0], 0);
        if (piped->executed_pipes_index > 1)
            dup2(fd_s[1], 1);
        else
            safe_close(fd[0]);
        close_pipe_ends(fd_s[0], fd_s[1]);
        dup2(fd_out[1], 1); // inverti os parametros
        env->exit_status = run_command_builtin(cmd_args, env, fd_out);
        safe_close(fd_out[1]);
        cleanup_and_exit_shell(env, env->exit_status); // testando
        exit(WEXITSTATUS(env->exit_status));
    }
    close_pipe_ends(fd_s[1], fd[0]);
    if (piped->executed_pipes_index > 1)
        fd[0] = fd_s[0];
    else
        safe_close(fd_s[0]);
    return (1);
}

int manage_builtin_execution(char **cmd_args, int *fd, t_env *env, t_pipe_state *piped)
{
    piped->children_count += 1;
    if (piped->executed_pipes_index)
    {
        if (!piped->is_redirection_or_pipe)
            env->exit_status = run_builtin_child(cmd_args, fd, env, piped);
        else
            env->exit_status = run_child_with_redirs(cmd_args, fd, env, piped);
    }
    else
        env->exit_status = manage_single_builtin_execution(cmd_args, fd, env, piped);
    return (env->exit_status);
}

int run_command_builtin(char **cmd_args, t_env *env, int *fd_out)
{
    int i;
    char *pwd;

    i = -1;
    while (cmd_args[++i])
    {
        if (ft_strcmp(cmd_args[0], "cd") == 0)
            env->exit_status = ft_cd(cmd_args[1], env);
        else if (ft_strcmp(cmd_args[0], "echo") == 0)
            env->exit_status = echo(cmd_args + 1, i - 1, fd_out, env);
        else if (ft_strcmp(cmd_args[0], "env") == 0)
            env->exit_status = ft_env(env);
        else if (ft_strcmp(cmd_args[0], "exit") == 0)
            env->exit_status = bash_exit(cmd_args + 1, i - 1, env);
        else if (ft_strcmp(cmd_args[0], "export") == 0)
            env->exit_status = ft_export(cmd_args[1], env);
        else if (ft_strcmp(cmd_args[0], "pwd") == 0)
        {
            pwd = ft_pwd(env, 1);
            return (free_envp(cmd_args), free(pwd), 0);
        }
        else if (ft_strcmp(cmd_args[0], "unset") == 0)
            return (ft_unset(cmd_args[1], env), free_envp(cmd_args), 0);
    }
    return (free_envp(cmd_args), env->exit_status);
}

/** @brief it compares the command with all 7 builtins
 * if any match is found, it runs the command with its argument, otherwise
 * it returns -1 to signalize that it didnt ran */
int run_command_builtin_2(char **arguments, t_env *env, int *fd)
{
    int i;
    char *pwd;

    i = 0;
    while (arguments[i])
        i++;
    if (ft_strcmp(arguments[0], "cd") == 0)
        return (ft_cd(arguments[1], env), 0);
    else if (ft_strcmp(arguments[0], "echo") == 0)
        return (echo(arguments + 1, i - 1, fd, env), 0);
    else if (ft_strcmp(arguments[0], "env") == 0)
        return (ft_env(env), 0);
    else if (ft_strcmp(arguments[0], "exit") == 0)
        return (bash_exit(arguments + 1, i - 1, env), 0);
    else if (ft_strcmp(arguments[0], "export") == 0)
        return (ft_export(arguments[1], env), 0);
    else if (ft_strcmp(arguments[0], "pwd") == 0)
    {
        pwd = ft_pwd(env, 1);
        return (free(pwd), 0);
    }
    else if (ft_strcmp(arguments[0], "unset") == 0)
        return (ft_unset(arguments[1], env), 0);
    return (-1);
}

// * @brief it splits the PATH variable ":" and tries to access the
//  * command to see if its inside this path. if not, frees and goes to
//  * the next. if it find it, returns the full path, otherwise
//  * it returns NULL
static char *loop_path(char *cmd, char *path_env)
{
    char **path;
    char *full_path;
    int i;
    i = 0;
    path = ft_split(path_env, ':');
    if (!path)
        return (NULL);
    while (path[i])
    {
        full_path = malloc(ft_strlen(path[i]) + ft_strlen(cmd) + 2);
        if (!full_path)
            return (NULL);
        ft_memcpy(full_path, path[i], ft_strlen(path[i]));
        full_path[ft_strlen(path[i])] = '/';
        ft_memcpy(full_path + ft_strlen(path[i]) + 1, cmd, ft_strlen(cmd) + 1);
        if (access(full_path, X_OK) == 0)
            return (free_envp(path), full_path);
        free(full_path);
        i++;
    }
    free_envp(path);
    return (NULL);
}

//  @brief checks if the command is already an absolute "/"
//  * or an relative "." path if not,
//  * it calls the loop_path to find the program
static char *get_path(char *cmd, char **envp)
{
    char *cmd_path;
    char *full_path;
    if (cmd[0] == '/' || cmd[0] == '.')
        return (ft_strdup(cmd));
    cmd_path = get_env("PATH", envp);
    if (!cmd_path)
        return (printf("PATH environment variable is not set.\n"), NULL);
    full_path = loop_path(cmd, cmd_path);
    return (free(cmd_path), full_path);
}

// @brief it runs the execve commands
/* static int	run_command_exec(char *cmd, char *const *argument, t_env *envp)
{
    char	*cmd_path;
    pid_t	pid;
    int		status;

    cmd_path = get_path(cmd, envp->parsed_env);
    if (!cmd_path)
        return (printf("Command not found: %s\n", cmd), 1); // tem que ser no stderr
    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, argument, envp->parsed_env) == -1)
            return (free(cmd_path), printf("execve: %s: %s\n",
                    cmd, strerror(errno)), 1);
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
        return (free(cmd_path), perror("fork"), 1);
    return (free(cmd_path), 0);
} */
static int run_command_exec(char *cmd, char *const *argument, t_env *env)
{
    char *cmd_path;
    pid_t pid;

    cmd_path = get_path(cmd, env->parsed_env);
    if (!cmd_path)
    {
        fprintf(stderr, "Command not found: %s\n", cmd);
        return (1);
    }
    pid = fork();
    if (pid == 0) // Processo filho
    {
        if (execve(cmd_path, argument, env->parsed_env) == -1)
        {
            free(cmd_path);
            fprintf(stderr, "execve error: %s: %s\n", cmd, strerror(errno));
            exit(127); // Finaliza corretamente
        }
    }
    else if (pid > 0) // Processo pai
    {
        waitpid(pid, &env->exit_status, 0);
        if (WIFEXITED(env->exit_status))
            env->exit_status = WEXITSTATUS(env->exit_status); // Obtém status do filho
        else
            env->exit_status = 1;
    }
    else // Erro no fork
    {
        perror("fork");
        free(cmd_path);
        return (1);
    }
    free(cmd_path);
    return (env->exit_status);
}

// @brief it first tries to execute the builtin functions,
//  * if its not inside that, it straight up goes to execve,
//  * returns error if none found
int execute(char *cmd, char *const *argument, t_env *env, int *fd)
{
    if (run_command_builtin_2((char **)argument, env, fd) == 0)
        return (0);
    else if (run_command_exec(cmd, argument, env) == 0)
        return (0);
    return (1);
}
