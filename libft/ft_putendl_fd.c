/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:54:33 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 14:36:37 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief Produz a string 's' para o descritor de arquivo fornecido
seguido por uma nova linha.
 @param s string para printar
 @param fd o file descriptor em qual se quer escrever*/
void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write (fd, "\n", 1);
}
/*int	main(void)
{
	ft_putendl_fd("ana", 1);
}*/