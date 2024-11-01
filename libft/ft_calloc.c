/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:54:07 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/09/04 14:45:18 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief aloca a memoria solicitada, calloc define a memoria alocada a zero.
 @param nmemb numeor de elementos a serem alocados.
 @param size tamanho os elementos.
 @return ponteiro para a memoria alocada, o null se a solicitacao falhar.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("ft_calloc: %p\n", ft_calloc(0, 0));
	printf("calloc: %p\n", calloc(0, 0)); 

	char *str;

	str = calloc(sizeof(char), 7);
	str[0] = 'm';
	str[1] = 'a';
	str[2] = 'r';
	str[3] = 'c';
	str[4] = 'e';
	str[5] = 'l';
	str[6] = 'o';
	printf("%s\n", str);
}*/