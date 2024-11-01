/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:59:11 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/28 13:02:50 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief procura a primeira ocorrência do caractere c 
nos primeiros n bytes da string apontada, pelo argumento str.
 @param str ponteiro para o bloco de memoria onde
a busca pelo character deve ser feita.
 @param c esse eh o valor passado como int, a funcao executa um pesquisa
 byte por byte usando a conversao unsiged int desse valor.
 @param n numero de bytes a sererm analizados.
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return ((unsigned char *) &s[i]);
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const void	*str = "melancia";
	int	c = 'a';
	unsigned int	n = 7;

	printf("ft_memchr: %p\n", ft_memchr(str, c, n));
}*/