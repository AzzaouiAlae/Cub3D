/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:19:16 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:19:19 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_parse.h"

bool	read_map(t_list *map, int fd)
{
	t_str	*line;

	line = read_line(fd, 1);
	if (line->count == 0)
		return (false);
	list_add(map, (long)line);
	while (1)
	{
		line = read_line(fd, 0);
		if (line->count == 0)
			break ;
		list_add(map, (long)line);
	}
	line = read_line(fd, 1);
	if (line->count || map->count < 3)
		return (false);
	return (true);
}

bool	check_map_tail(t_list *map, t_str **lines, int i, int j)
{
	int	max_hiegh;
	int	max_width;

	max_hiegh = map->count - 1;
	max_width = lines[i]->count - 1;
	if (i == 0 || max_hiegh <= i || j == 0 || max_width <= j)
		return (false);
	if (lines[i]->content[j + 1] == ' ' || lines[i]->content[j - 1] == ' ')
		return (false);
	if (lines[i - 1]->count - 1 < j || lines[i + 1]->count - 1 < j)
		return (false);
	if (lines[i - 1]->content[j] == ' ' || lines[i + 1]->content[j] == ' ')
		return (false);
	return (true);
}

bool	init_player(t_player *player, char ch, int i, int j)
{
	static int	count;

	if (count)
		return (false);
	count++;
	if (ch == 'c')
		return (true);
	if (ch == 'N')
		player->angle = 90;
	else if (ch == 'S')
		player->angle = 270;
	else if (ch == 'E')
		player->angle = 0;
	else if (ch == 'W')
		player->angle = 180;
	player->map_pos.x = j;
	player->map_pos.y = i;
	player->pixl_pos.x = player->map_pos.x * TILESIZE + (TILESIZE / 2);
	player->pixl_pos.y = player->map_pos.y * TILESIZE + (TILESIZE / 2);
	return (true);
}

bool	check_map(t_list *map, t_player *player)
{
	int		i;
	int		j;
	t_str	**lines;

	i = 0;
	lines = map->content;
	while (lines[i])
	{
		j = 0;
		while (lines[i]->count > j)
		{
			if (!ft_strchr("10NSEW D", lines[i]->content[j]))
				return (false);
			if (!ft_strchr("1 ", lines[i]->content[j]) && !check_map_tail(map,
					lines, i, j))
				return (false);
			if (ft_strchr("NSEW", lines[i]->content[j]) && init_player(player,
					lines[i]->content[j], i, j) == false)
				return (false);
			j++;
		}
		i++;
	}
	return (!init_player(NULL, 'c', 0, 0));
}
