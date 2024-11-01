/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:21:16 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/11 20:43:37 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (2048);
}
/*#include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("%i\n", ft_isdigit(49));
    printf("%i\n", isdigit(49));
}*/