/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:27:23 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/01 19:44:38 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

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

t_env	*ft_lstnew_env(t_mshell *shell, char *str, char *ptr)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	my_malloc(shell->block, new);
	if (!new)
		return (0);
	new->name = str;
	new->content = ptr;
	new->next = NULL;
	return (new);
}
