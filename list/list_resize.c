/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_list_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:44:19 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/28 19:11:06 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_resize(t_list *list, int capacity)
{
	void	*mem;
	void	*tmp;

	mem = ft_calloc(list->size_of_type, capacity);
	ft_memcpy(mem, list->content, list->count * list->size_of_type);
	tmp = list->content;
	list->content = mem;
	list->capacity = capacity;
	ft_free(tmp);
}
