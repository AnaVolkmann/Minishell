/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:21:01 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/02 15:07:13 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_substrings(char *str, char del)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 1;
	result = 0;
	while(str[i] && str)
	{
		if (str[i] != del)
		{
			if (j)
				result++;
			j = 0;
		}
		else
			j = 1;
		i++;
	}
	return (result);
}

