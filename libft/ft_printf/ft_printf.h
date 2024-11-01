/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:01:05 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/05/09 18:43:43 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int	ft_printf(const char *str, ...);
int	ft_putstr(char *str);
int	ft_putchar(int c);
int	ft_putnbr(int nbr, int u);
int	ft_putpointer(unsigned long nbr);
int	ft_puthexa(unsigned int nbr, const char c);
int	ft_putpointerhexa(unsigned long nbr, const char c);

#endif