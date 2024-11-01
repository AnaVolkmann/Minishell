/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:09:43 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/09/02 15:39:45 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief procura pela primeira ocorencia do char c na string
 apontada por str.
 @param str string a ser percorida
  @param c charcarter a ser procurado.
  @return ponteiro para a primeira ocorrencia do char c na string str
  ou null, se o char nao for encontrado.*/
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *) &str[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	int	c = 0;
	const char	*str = "ajijia";

	printf("%s\n", ft_strchr(str, c));
}*/