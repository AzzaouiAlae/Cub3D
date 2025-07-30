/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:45:00 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/28 19:10:06 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	ft_free_all(void)
{
	t_mem_list	**list;
	t_mem_list	*tmp;
	void		*mem;

	list = ft_mem_list();
	if (!list || !(*list))
		return ;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->mem);
		free(tmp);
	}
	mem = current_working_mem(NULL, 0);
	free(mem);
	current_working_mem(NULL, 1);
}

void	find_to_free(void *mem)
{
	t_mem_list	*head;
	t_mem_list	*prev;

	head = (*ft_mem_list());
	while (head)
	{
		prev = head;
		head = head->next;
		if (head && head->mem == mem)
		{
			prev->next = head->next;
			free(head->mem);
			free(head);
			return ;
		}
	}
	free(mem);
}

void	ft_free(void *mem)
{
	t_mem_list	**mems;
	t_mem_list	*head;

	mems = ft_mem_list();
	if (!(*mems))
		return ;
	head = (*mems);
	if ((*mems)->mem == mem)
	{
		(*mems) = (*mems)->next;
		free(head->mem);
		free(head);
		return ;
	}
	find_to_free(mem);
}
