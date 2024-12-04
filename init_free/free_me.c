/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:21:06 by lufiguei          #+#    #+#             */
/*   Updated: 2024/12/04 15:24:52 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_and_exit_shell(t_env *env, int status)
{
	if (env)
	{
		if (env->parsed_env)
			free_envp(env->parsed_env);
		if (env->shell)
			free(env->shell);
	}
	free(env);
	exit(status);
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
