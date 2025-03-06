/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:21:06 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/19 11:49:47 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	string_to_int(char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	return (nbr);
}

void	cleanup_and_exit_shell(t_env *env, int status)
{
	if (env)
	{
		if (env->parsed_env)
			free_envp(env->parsed_env);
	}
	free(env);
	exit(status);
}

void	ft_exit(char **cmd, t_env *env)
{
	if (cmd[1] && cmd[2])
	env->exit_status = 1;
	else if (cmd[1] && !is_string_numeric(cmd[1]))
	env->exit_status = 255;
	else if (cmd[1])
	env->exit_status = string_to_int(cmd[1]);
	free_envp(cmd);
	exit(env->exit_status);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_ast(t_ast_node **ast)
{
	t_ast_node	*tmp;

	if (!ast || !*ast)
		return ;
	tmp = *ast;
	free_ast(&tmp->left);
	free_ast(&tmp->right);
	if (tmp->args)
		free_envp(tmp->args);
	free(tmp);
	*ast = NULL;
}

void	free_parsed_env(t_env *env)
{
	int	i;

	if (env && env->parsed_env)
	{
		i = 0;
		while (env->parsed_env[i])
		{
			free(env->parsed_env[i]);
			i++;
		}
		free(env->parsed_env);
		env->parsed_env = NULL;
	}
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
	else
		return ;
}