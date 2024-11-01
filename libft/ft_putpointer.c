/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:34:51 by anavolkmann       #+#    #+#             */
/*   Updated: 2024/06/26 15:30:39 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpointer(unsigned long nbr)
{
	int	result;

	result = 0;
	if (!nbr)
		return (write(1, "(nil)", 5));
	else
	{
		result += ft_putstr("0x");
		result += ft_putpointerhexa(nbr, 'x');
	}
	return (result);
}
