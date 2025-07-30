/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:37 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 05:35:53 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "../list/list.h"

typedef struct key_value
{
	char	*key;
	void	*value;
}			t_key_value;

typedef struct s_map
{
	void	*content;
	int		count;
	int		max_size;
	int		capacity;
}			t_map;

int			map_hash_function(char *str);
t_map	*map_new(void);
t_map	*map_new_capacity(int capacity);
void		map_add(t_map *map, char *key, void *value);
void		*map_get(t_map *map, char *key);
void		map_delete(t_map *map, char *key);
void		map_clear(t_map *map);
int			next_prime(int n);
void		map_resize(t_map *map, int capacity);
void		map_foreach(t_map *map, void (*f)(t_key_value *));

#endif