/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointerhexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:13:28 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/06/26 15:30:39 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpointerhexa(unsigned long nbr, const char c)
{
	char	*base;
	int		result;

	result = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		result += ft_putpointerhexa((nbr / 16), c);
		result += ft_putpointerhexa((nbr % 16), c);
	}
	else
		result += write(1, &base[nbr], 1);
	return (result);
}
