/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:45:07 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/28 19:10:10 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	add_mem(t_mem_list *node)
{
	t_mem_list	**list;
	t_mem_list	*head;

	list = ft_mem_list();
	if (!(*list))
	{
		*list = node;
		return ;
	}
	head = *list;
	while (head && head->next)
		head = head->next;
	head->next = node;
}

void	save_mem(void *mem)
{
	t_mem_list	*new;

	current_working_mem(mem, 0);
	new = ft_calloc_without_save(1, sizeof(t_mem_list));
	current_working_mem(0, 1);
	new->mem = mem;
	add_mem(new);
}
