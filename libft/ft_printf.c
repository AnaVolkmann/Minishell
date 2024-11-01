/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:50:50 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/06/26 15:32:57 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arguments(char s, va_list ap)
{
	int	result;

	result = 0;
	if (!s)
		return (0);
	else if (s == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (s == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (s == 'p')
		return (ft_putpointer(va_arg(ap, unsigned long)));
	else if (s == 'd' || s == 'i')
		return (ft_putnbr(va_arg(ap, int), 0));
	else if (s == 'u')
		return (ft_putnbr(va_arg(ap, unsigned int), 1));
	else if (s == 'x' || s == 'X')
		return (ft_putpointerhexa(va_arg(ap, unsigned int), s));
	else if (s == '%')
		return (write(1, "%", 1));
	return (0);
}

/** @brief Realiza impressao de textos no terminal, possui numero de//
 parametros vaiado, tantos quanto for necessario.
 @return o comprimento da string gerada.
*/
/* linha: 55- verifico se existe um sinal de %, caso nao encontre,//
o char sera
immpresso e somado a count, que eh o controle de quantos chars//
foram impressos e tb o retorno*/
int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, str);
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '%')
		{
			count += ft_arguments(*(++str), ap);
		}
		else
			count += write(1, str, 1);
		++str;
	}
	va_end(ap);
	return (count);
}
/* 
#include <stdio.h>

int main()
{
	int i = 1544;
    int *var; var = &i;
    char *str = "TESTE STRING";
    char c = 'c';
    int f = 0xffffffff;
    int rvaluer;
    int rvalueo;

    rvaluer = ft_printf("\n\nD = [%d]\nPTR = //
	[%p]\nSTR = [%s]\nC = [%c]\nhex = [%x]\nHEX = [%X]\n", i, var, str, c, f, f);
    rvalueo = printf("\n\nD = [%d]\nPTR = [%p]\nSTR = //
	[%s]\nC = [%c]\nhex = [%x]\nHEX = [%X]\n", i, var, str, c, f, f);
    ft_printf("\n\nReturn Value Replica: [%d]", rvaluer);
    printf("\n\nReturn Value Original: [%d]", rvalueo);
} */