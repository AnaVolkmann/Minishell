/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:41 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/09/04 14:41:08 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief remove os characteres especificados em set de s1 no inicio
e no final da string 
 @param s1 string a ser aparada
 @param set characeres a serem cortados
 @return a string aparada
*/
// linha 38 - Extrai a substring de s1 que começa
// no índice first e termina no índice last - 1.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	char	*final;

	final = NULL;
	if (s1 && set)
	{
		first = 0;
		last = ft_strlen(s1);
		while (s1[first] && first < last && ft_strchr(set, s1[first]) != NULL)
			first++;
		while (last > first && ft_strchr(set, s1[last - 1]) != NULL)
			last--;
		final = ft_substr(s1, first, last - first);
	}
	return (final);
}
/*#include <stdio.h>

int	main(void)
{
	const char	s1[] = "abcdef";
	const char	set[] = "a";
	printf("%s\n", ft_strtrim(s1, set));
}*/