/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_map_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:14 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 10:44:55 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	map_clear(t_map *map)
{
	int			index;
	int			i;
	t_list	**lists;

	index = -1;
	lists = map->content;
	while (++index < map->capacity)
	{
		if (!lists[index])
			continue ;
		i = 0;
		while (lists[index]->count > i)
		{
			list_delete(lists[index], i);
			i++;
		}
	}
}
