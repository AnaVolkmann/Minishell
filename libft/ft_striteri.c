/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:13:21 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 14:49:07 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static void	test(unsigned int n, char *s)
{
	*s += n;
} */
/** @brief aplica a funcao 'f' a cada char da strig passada como arg
passando seu index como primeiro para, cada char passa pela funcao para
ser modificada, se necessario.
 @param s string a ser iterada
 @param f funcao a ser aplicada a cada char
 @return none 
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*#include <stdio.h>

int	main(void)
{
	char s[] = "abc";
	printf("antes: %s\n", s);
	ft_striteri(s, test);
	printf("depois: %s\n", s);
} */