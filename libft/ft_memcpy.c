/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:50:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/28 12:54:27 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief copia n caractares da area de memoria de scr, para a area
de memoria de dest.
 @param dest ponteiro para a matriz de destino onde o conteúdo deve
 ser copiado.
  @param scr ponteiro para a fonte de dados a ser copiada.
  @param n numero de bytres a serem copiados.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dtr;
	char	*str;
	size_t	i;

	dtr = (char *)dest;
	str = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dtr[i] = str[i];
		i++;
	}
	return (dest);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	src[] = "galera";
	char	dest[] = "de cauboi";
	size_t	n = 5;
	
	printf("%s\n", (char *)ft_memcpy(dest, src, n));
}*/