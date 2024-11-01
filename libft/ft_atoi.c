/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:52:21 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 13:01:46 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief converte o argumento strig str para um inteiro(tpe int)
 @param str representacao em string de um numero inteiro.
 @return numero integral convertido como um valor int. se nenhuma conversao 
 valida puder ser realizada, o retorno eh zero.
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	number;

	i = 0;
	number = 0;
	neg = 1;
	while (str[i] != '\0' && ((str[i] <= 13 && str[i] >= 9) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * neg);
}
/*#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char s[] = " 1234567a";

    printf("ft_atoi:%i\n", ft_atoi(s));
    printf("atoi original:%i\n", atoi(s));
}*/