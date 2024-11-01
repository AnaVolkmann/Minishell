/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:06:55 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/09/04 14:47:29 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief concatena duas strings.
 @param s1 e s2 sao string a serem concatenadas.
 @return uma nova string resultado da juncao de s1 e s2.
*/
char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;
	int		size;

	if (!s1)
		s1 = ft_calloc(sizeof(char), 1);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *) ft_calloc(sizeof(char), size);
	if (result == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	free(s1);
	return (result);
}
/*#include <stdio.h>

int	main(void)
{
	char const	str1[] = "abc";
	char const	str2[] = "def";

	printf("antes s2:%s\n", str1);
	printf("antes s1:%s\n", str2);
	printf("depois do join: %s\n", ft_strjoin(str1, str2));
}*/