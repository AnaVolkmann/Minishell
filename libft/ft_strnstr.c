/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:12:06 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 17:08:56 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief lozaliza uma substring em uma string.
 @param big string na qual a substring sera procurada.
 @param little substring a ser procurada e big.
 @param len tamanho ate aonda a big deve ser percorrida
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] != '\0' && big[i + j] == little[j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("ft_strnstr = %s\n", ft_strnstr("ana banana", "bana", 10));
	//printf("strnstr = %s\n", strnstr("ana banana", "bana", 10));
}*/