/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_list_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:18 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/03/23 15:48:13 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_delete_char(char *s, int count, int index)
{
	while (index < count - 1)
	{
		s[index] = s[index + 1];
		index++;
	}
	if (index == count - 1)
		s[index] = 0;
}

void	list_delete_int(int *nums, int count, int index)
{
	while (index < count - 1)
	{
		nums[index] = nums[index + 1];
		index++;
	}
	if (index == count - 1)
		nums[index] = 0;
}

void	list_delete_long(long *nums, int count, int index)
{
	while (index < count - 1)
	{
		nums[index] = nums[index + 1];
		index++;
	}
	if (index == count - 1)
		nums[index] = 0;
}

void	list_delete(t_list *list, int index)
{
	if (index >= list->count)
		return ;
	if (list->size_of_type == 1)
		list_delete_char(list->content, list->count, index);
	else if (list->size_of_type == 4)
		list_delete_int(list->content, list->count, index);
	else if (list->size_of_type == 8)
		list_delete_long(list->content, list->count, index);
	else
		return ;
	list->count--;
}

void	list_clear(t_list *list)
{
	if (!list)
		return ;
	ft_bzero(list->content, list->count * list->size_of_type);
	list->count = 0;
}
