/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:11:29 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/05 18:17:18 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_error(char *arg)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

static int	str_is_digit(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	bash_exit(char **args, int arg_count, t_shell *shell)
{
	long int	exit_value;

	ft_putendl_fd("exit", 2);
	if (arg_count == 0)
    	return (update_exit(0, shell), exit(0), 0);
    if (arg_count == 1)
	{
		if (!str_is_digit(args[0]))
			return (update_exit (2, shell), exit_error(args[0]), 2);
		else
		{
			exit_value = strtol(args[0], NULL, 10);
			if (exit_value > INT_MAX || exit_value < INT_MIN)
			{
				ft_putstr_fd("bash: exit: overflow or underflow\n", 2);
				return (update_exit (2, shell), exit(2), 2);
			}
			exit((int)exit_value);
		}
	}
	return (update_exit(2, shell), ft_putstr_fd("bash: exit: too many arguments\n", 2), 2);
}

void update_exit(int i, t_shell *shell)
{
    shell->exit_status = i;
}

/** @brief I HAVE NO IDEA IF THIS IS HOW ITS SUPPOUSED TO BEEEEEEE */
/*
void exit_cmd(char **cmd_args, t_shell *shell)
{
    ft_printf(1, "exit\n");

    if (!cmd_args[1]) {
        free_and_exit(shell);
    } 
    else if (str_is_digit(cmd_args[1])) {
        exit_number(cmd_args, shell);
    } 
    else {
        shell->exit_status = EXIT_SYNTAX;
        ft_printf(STDERR_FILENO, "minishell: exit:
        	%s: numeric argument required\n", cmd_args[1]);
        free_and_exit(shell);
    }
}

void exit_line(t_shell *shell)
{
    int status = shell->exit_status;
    free_envs(shell->envp);
    free(shell->line);
    free(shell);
    ft_printf(STDOUT_FILENO, "exit\n");
    exit(status);
}

void exit_number(char **cmd_args, t_shell *shell)
{
    int status = 0;
    int i = 0;

    if (cmd_args[2])
	{
        shell->exit_status = EXIT_FAILURE;
        ft_printf(STDERR_FILENO, "minishell: exit: too many arguments\n");
        return;
    }
    while (cmd_args[1][i] != '\0')
	{
        if (!(cmd_args[1][i] >= '0' && cmd_args[1][i] <= '9')
        	&& !(i == 0 && (cmd_args[1][i] == '-'
        		|| cmd_args[1][i] == '+'))) {
            shell->exit_status = EXIT_SYNTAX;
            ft_printf(STDERR_FILENO, "minishell: exit:
            	%s: numeric argument required\n", cmd_args[1]);
            return;
        }
        i++;
    }
    status = ft_atoi(cmd_args[1]);
    if (status < 0)
	{
        while (status < 0) {
            status += 256;
        }
    }
    status %= 256;
    shell->exit_status = status;
    free_and_exit(shell);
}

int str_is_digit(char *str)
{
    int i = 0;

    if (str[i] == '\0') {
        return 0;
    }
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }
    while (str[i] != '\0') {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return 0;
        }
        i++;
    }
    return 1;
} */