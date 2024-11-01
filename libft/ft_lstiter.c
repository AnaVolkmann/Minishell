/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:54:46 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 14:26:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief itera a lista 'lst' e aplica a funcao 'f' no 
conteudo de cada noh.
 @param lst endereco de um ponteiro para um noh
 @param f endereco da funcao usada para iterar na lista.
*/
/* #include <stdio.h>

void	ft_testiter(void *ptr)
{
	printf("%s\n", (char *)ptr + 1);
} */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/* 


int	main(void)
{
	t_list	*lista;
	t_list	*lista2 = NULL;

	lista = malloc(sizeof(t_list));
	lista2 = malloc(sizeof(t_list));
	lista->content = "43";
	lista->next = lista2;
	lista2->content = "44";
	lista2->next = 	NULL;
	ft_lstiter(lista, ft_testiter);
	return (0);
} */