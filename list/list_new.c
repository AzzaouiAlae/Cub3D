/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_list_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:44:11 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/28 19:18:17 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_new(int size_of_type)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	list->content = ft_calloc(size_of_type, 32);
	list->size_of_type = size_of_type;
	list->count = 0;
	list->capacity = 32;
	list->type = 0;
	return (list);
}

t_list	*list_new_capacity(int size_of_type, int capacity)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	list->content = ft_calloc(size_of_type, capacity + 1);
	list->size_of_type = size_of_type;
	list->count = 0;
	list->capacity = capacity + 1;
	list->type = 0;
	return (list);
}
