/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:21:06 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/29 15:06:49 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit_shell(t_env *env, int status)
{
	if (env)
	{
		free_string_array(env->original_env);
		free_environment_variables(env->parsed_env);
		free(env);
	}
	exit(status);
}

void free_envp(void **envp)
{
	int i = 0;

	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp)
		free_envp(shell->envp);
}

void	free_ast(t_ast_node **ast)
{
	t_ast_node *tmp;

	if (!ast || !*ast)
		return ;
	tmp = *ast;
	free_ast(&tmp->left);
	free_ast(&tmp->right);
	if (tmp->args)
		free_envp(tmp->args);
	*ast = NULL;
}
