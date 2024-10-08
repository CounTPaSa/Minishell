/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:46:58 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 19:32:44 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

void	ft_lstadd_back_memory(t_block **lst, t_block *new)
{
	t_block	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_block	*ft_lstnew_memory(void *content)
{
	t_block	*new;

	new = malloc(sizeof(t_block));
	if (!new)
		return (0);
	new->allocate = content;
	new->next = NULL;
	return (new);
}

void	ft_lstdelone_memory(t_block *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->allocate);
	lst->allocate = NULL;
	free(lst);
}

void	ft_lstclear_memory(t_block **lst, void (*del)(void *))
{
	t_block	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		ft_lstdelone_memory(*lst, del);
		*lst = ptr;
	}
	*lst = NULL;
}
