/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_list_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:59 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/03/23 15:48:13 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_inset_char(char *s, int count, char value, int index)
{
	while (count > index)
	{
		s[count] = s[count - 1];
		count--;
	}
	s[index] = value;
}

void	list_inset_int(int *nums, int count, int value, int index)
{
	while (count > index)
	{
		nums[count] = nums[count - 1];
		count--;
	}
	nums[index] = value;
}

void	list_inset_long(long *nums, int count, long value, int index)
{
	while (count > index)
	{
		nums[count] = nums[count - 1];
		count--;
	}
	nums[index] = value;
}

void	list_inset_at(t_list *list, int index, long item)
{
	if (!list)
		return ;
	if (!list->count)
	{
		list_add(list, item);
		return ;
	}
	if (list->capacity - 1 == list->count)
		list_resize(list, list->capacity * 2);
	if (list->size_of_type == 1)
		list_inset_char(list->content, list->count, (char)item, index);
	else if (list->size_of_type == 4)
		list_inset_int(list->content, list->count, (int)item, index);
	else if (list->size_of_type == 8)
		list_inset_long(list->content, list->count, (long)item, index);
	(list->count)++;
}
