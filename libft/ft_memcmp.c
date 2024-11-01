/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:23:34 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/28 12:58:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief compara os primeiros n bytes
da área de memória str1 e da área de memória str2.
 @param str1 e str2 ponteiros para um bloco de memoria.
  @param n numeros de bytes a serem comparados.
 */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const	void *str1 = "abc";
	const char	*str2 = "abb";
	size_t	n = 3;

	printf("ft_memcmp: %i\n", ft_memcmp(str1, str2, n));
}*/