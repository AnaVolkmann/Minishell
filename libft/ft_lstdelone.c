/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:30:48 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/24 17:29:22 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief Toma como parâmetro um nó e libera a memória do
o conteúdo do nó usando a função 'del' fornecida
como parâmetro e libere o nó.
 @param lst  o noh para liberar mem. 
 @param del  endereco da funcao usada para deletar o conteudo. 
 @return none.
*/
/* void	ft_delete(void *conteudo)
{
	free(conteudo);
} */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

/* #include <stdio.h>

int	main(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
    list->content = ft_strdup("abcd");
	ft_lstdelone(list, ft_delete);
	printf("o node foi corretamente excluido\n");
} */