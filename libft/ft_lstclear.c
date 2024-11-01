/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:25:42 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/30 14:26:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief Deleta e libera o node dado e cada sucessor deste noh,
o poteiro deve se setado a nulo.
 @param lst endereco de um ponteiro para um noh
 @param del endereco da funcao usada para deletar conteudo do noh.
*/
/* void	ft_delete_node(void *conteudo)
{
	free(conteudo);
} */
void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*ptr;
	t_list	*next;

	ptr = *lst;
	while (ptr)
	{
		next = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = next;
	}
	*lst = NULL;
}

/* #include <stdio.h>

int	main(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
    list->content = ft_strdup("abcd");
	ft_lstclear(&list, ft_delete_node);
	printf("o node foi corretamente excluido\n");
} */