/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:30 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 17:25:53 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief cria uma substring, que comeca em start e tem tamanho
maximo definido por len.
 @param s string da qual se criara uma substring. 
  @param start o indice inicial da substring. 
  @param len tamanho maximo da substring.
  @return a substring.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* #include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_substr("abc", 1, 4));
} */