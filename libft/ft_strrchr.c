/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:29:00 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 17:09:58 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief procura a primeira ocorrencia do char c em s*/

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == ((char)c))
			return ((char *)&s[i]);
		i--;
	}
	return ((char *)0);
}
/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	int	c = 0;
	const char	*s = "ajijia";

	printf("%s\n", ft_strrchr(s, c));
}*/