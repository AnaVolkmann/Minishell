/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:30:20 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 13:32:23 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief converte um valor integer em uma string terminada em nulo
usando a base especificada e amarmazena o resultado na matriz fornecida
pero param str.
 @param n valor a ser convertido para uma string.
 @return um ponteiro para a string terminada em nulo.
*/
// lenofn -recebe o número inteiro n e retorna o número de dígitos
//necessários para representar n.
// linha 36- incrementa meu len para considerar o sinal negativo.
// linha 39- dividido por 10 para remover o último dígito, e
// len é incrementada para contar o número de dígitos.
int	lenofn(int n)
{
	long	numb;
	int		len;

	numb = (long)n;
	len = 1;
	if (!n)
		return (1);
	if (numb < 0)
	{
		numb = numb * (-1);
		len ++;
	}
	while (numb >= 10)
	{
		numb = numb / 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	numb;
	int		tam;

	tam = lenofn(n);
	numb = (long)n;
	result = (char *)malloc(sizeof(char) * (tam + 1));
	if (!result)
		return (NULL);
	result[tam] = '\0';
	if (numb < 0)
	{
		result[0] = '-';
		numb = numb * (-1);
	}
	while (tam-- && result[tam] != '-')
	{
		result[tam] = numb % 10 + '0';
		numb = numb / 10;
	}
	return (result);
}
/* #include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(-623));
	return (0);
}  */