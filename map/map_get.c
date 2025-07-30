/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_map_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:28 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:22:29 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_func/ft_func.h"
#include "map.h"

void	*map_get(t_map *map, char *key)
{
	int			index;
	int			i;
	t_list	**lists;
	t_key_value	**key_values;

	index = map_hash_function(key) % map->capacity;
	lists = map->content;
	if (!lists[index])
		return (NULL);
	i = 0;
	while (lists[index]->count > i)
	{
		key_values = lists[index]->content;
		if (!ft_strcmp(key_values[i]->key, key))
			return (key_values[i]->value);
		i++;
	}
	return (NULL);
}
