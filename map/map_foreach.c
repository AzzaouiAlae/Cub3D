/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_map_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:25 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 10:45:12 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	exec_func(t_key_value **kvps, int count, void (*f)(t_key_value *))
{
	int	j;

	j = 0;
	while (j < count)
	{
		f(kvps[j]);
		j++;
	}
}

void	map_foreach(t_map *map, void (*f)(t_key_value *))
{
	int			i;
	t_list	**lists;

	if (!map || !f)
		return ;
	i = 0;
	lists = map->content;
	while (i < map->capacity)
	{
		if (lists[i])
			exec_func(lists[i]->content, lists[i]->count, f);
		i++;
	}
}
