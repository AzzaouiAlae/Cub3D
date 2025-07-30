/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:44:24 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/29 13:16:19 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CS_LIST_H
# define CS_LIST_H
# include "../garbage_collector/garbage_collector.h"
# include <stdarg.h>
# include <unistd.h>

typedef struct s_list
{
	void	*content;
	int		size_of_type;
	int		count;
	int		capacity;
	int		type;
}			t_list;

void		list_add(t_list *list, long item);
void		list_add_range(t_list *list, int count, void *arr);
t_list	*list_new(int size_of_type);
t_list	*list_new_capacity(int size_of_type, int capacity);
void		list_resize(t_list *list, int capacity);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		list_delete(t_list *list, int index);
void		list_inset_at(t_list *list, int index, long item);
int			list_contains(t_list *list, long item);
void		list_clear(t_list *list);

#endif