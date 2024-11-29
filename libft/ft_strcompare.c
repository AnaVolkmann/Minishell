/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcompare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:29:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/11/29 15:13:33 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief Compares two strings up to a specified maximum length.
 * This function compares the characters of two strings `s_1` 
 * and `s_2` up to the given maximum number of characters (`max`). 
 * It returns 1 if the strings match exactly up to the `max`
 *  length, and 0 if they do not.
 *
 * @param s_1 The first string to compare.
 * @param s_2 The second string to compare.
 * @param max The maximum number of characters to compare.
 * 
 * @return 1 if the strings match up to the `max` length, 0 
 * otherwise.*/
int	ft_strcompare(char *s_1, char *s_2, int max)
{
	int	a;

	a = 0;
	while (a < max && *s_1 && *s_2 && s_1[a] == s_2[a])
		a++;
	if (sizeof_str(s_1, '\0') == a && a == max)
		return (1);
	return (0);
}
