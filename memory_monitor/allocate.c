/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:49:42 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/04 00:06:57 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// Mallocs the starter block
t_block	*malloc_starter(void)
{
	t_block	*block;

	block = ft_calloc(1, sizeof(t_block));
	if (!block)
		error_exit(MALLOC, NULL, FALSE);
	return (block);
}

// Mallocs the memory and returns the pointer
// void türünden int tiplemesine dönücek fonk
void	*my_malloc(t_block *block, void *address)
{
	t_block	*new_block;

	if (block == NULL)
		return (NULL);
	new_block = ft_lstnew_memory(address);
	if (new_block != NULL)
	{
		ft_lstadd_back_memory(&block, new_block);
		return (TRUE);
	}
	return (printf(MALLOC), NULL);
}

// Free's the malloced memory node
// bu denenicek
void	free_malloc(t_block *block, void *delete_adress)
{
	t_block	*current_node;
	t_block	*previous_node;

	if (block == NULL || delete_adress == NULL)
		return ;
	current_node = block;
	previous_node = NULL;
	while (current_node != NULL && current_node->allocate != delete_adress)
	{
		previous_node = current_node;
		current_node = current_node->next;
	}
	if (current_node != NULL)
	{
		if (previous_node == NULL)
			block = current_node->next;
		else
			previous_node->next = current_node->next;
		if (current_node->allocate)
			free(current_node->allocate);
		free(current_node);
	}
}

// Free's all the malloced memory and the block
void	end_malloc(t_mshell *shell)
{
	// rl_clear_history bu kısıma da eklenebilir
	if (shell->env)
		free_env(shell);
	ft_lstclear_memory(&shell->block, free);
}
