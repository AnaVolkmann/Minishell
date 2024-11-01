/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:35:52 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/11 20:43:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (16384);
}
/*#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%i\n", ft_isprint('a'));
	printf("%i\n", isprint('a'));
}*/