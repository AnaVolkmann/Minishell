/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:41:51 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 14:44:48 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief cria uma nova string, duplicando o imput.
 @param s string a ser duplicada
 @return nova string copia do imput
*/

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*s1 = "ana";

	printf("ft_strdup: %s\n", strdup(s1));
}*/