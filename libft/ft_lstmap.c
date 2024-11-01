/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:53:30 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/04/28 12:05:24 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @brief Itera a lista ‘lst’ e aplica a função
'f' no conteúdo de cada nó. Cria uma nova
lista resultante das sucessivas aplicações de
a função 'f'. A função 'del' é usada para
excluir o conteúdo de um nó, se necessário.
 @param lst: o endereco de um ponteiro para um nó.
 @param f: o endereco de uma funcao utilizada para iterar a lista.
 @param del: O endereço da função usada para excluir 
 o conteúdo de um nó, se necessário.
*/	
/* 
void	ft_delete(void *list)
{
	free(list);
} 

void	*transform_content(void *content)
{
	size_t	i;
	char	*str;
	char	*result;

	if (content == NULL)
		return (NULL);
	str = (char *)content;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		result[i] = ft_toupper(result[i]);
		i++;
	}
	return (result);
}
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*newlist;
	void	*content;

	if (!f || !del || !lst)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (!temp)
		{
			del(content);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, temp);
		lst = lst->next;
	}
	return (newlist);
}

/* #include <stdio.h>

int	main(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
    list->content = ft_strdup("abcd");
	t_list *newlist = ft_lstmap(list, transform_content, ft_delete);
	if (!newlist)
    {
        printf("Failed to create new list\n");
        free(list->content);
        free(list);
        return (1);
    }

    printf("Original content: %s\n", (char *)list->content);
    printf("Transformed content: %s\n", (char *)newlist->content);

    // Libera a memória alocada
    ft_lstclear(&newlist, ft_delete);
	return (0); 
}*/