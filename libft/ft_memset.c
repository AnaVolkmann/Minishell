/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:19:32 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/28 13:04:19 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief copia o caractere c para os primeiros n caracteres 
da string apontada, pelo argumento str.
 @param s ponteiro para o bloco de memoria a ser preenchido.
 @param c o valor a ser definido, (passado como um int,
a funcao converte utilizanco cast para unsiged char).
 @param n (limitador) numero de bytes a serem definidos para o valor.
 @return um pontriro para a area de memoria 's'.
 */
void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)str;
	i = 0;
	while (i < n)
	{
		ptr[i] = (char) c;
		i++;
	}
	return (str);
}
/* #include <string.h>
#include <stdio.h>

int	main(void)
{
	char a[] = "ana";
	char b[] = "ana";

	printf("ft_memset: %s\n", (char *)ft_memset(a, 's', 4));
	printf("memset: %s\n", (char *)memset(b, 's', 4));
} */