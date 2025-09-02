/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:50:41 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:53:53 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../player/player.h"
#include "../raycasting/raycasting.h"
#include "map_game.h"

void	init_map_pos(t_line *map_pos, t_point *start)
{
	map_pos->start.x = g_vars()->player.pixl_pos.x - (MAP_W / 2);
	map_pos->start.y = g_vars()->player.pixl_pos.y - (MAP_HEIGHT / 2);
	map_pos->end.x = map_pos->start.x + MAP_W;
	map_pos->end.y = map_pos->start.y + MAP_HEIGHT;
	start->x = map_pos->start.x;
	start->y = map_pos->start.y;
}

t_pos_type	check_pos(double x, double y)
{
	t_str	**the_map;
	int		row;
	int		col;

	the_map = g_vars()->map->content;
	row = y / TILESIZE;
	col = x / TILESIZE;
	if (row < 0 || g_vars()->map->count <= row || y < 0)
		return (e_invalid);
	if (col < 0 || the_map[row]->count <= col || x < 0)
		return (e_invalid);
	if (the_map[row]->content[col] == '1')
		return (e_wall);
	else if (the_map[row]->content[col] == 'D')
		return (e_closed_gate);
	else if (the_map[row]->content[col] == 'd')
		return (e_opened_gate);
	else if (the_map[row]->content[col] == ' ')
		return (e_space);
	return (e_empty);
}

int	get_pos_color(t_pos_type pos_type)
{
	t_color	color;

	if (pos_type == e_wall)
		color = (t_color){0, 0, 255, 0};
	else if (pos_type == e_empty)
		color = (t_color){50, 50, 50, 0};
	else if (pos_type == e_invalid || pos_type == e_space)
		color = (t_color){20, 20, 20, 0};
	else if (pos_type == e_closed_gate)
		color = (t_color){120, 120, 120, 0};
	else if (pos_type == e_opened_gate)
		color = (t_color){255, 0, 0, 0};
	return (*((int *)&(color)));
}

int	get_color(int x, int y, t_line map_pos, t_pos_type pos_type)
{
	int	color;

	if (y == 0 || x == 0 || x == MAP_W - 1 || y == MAP_HEIGHT - 1)
		color = 0xFFFFFF;
	else
	{
		color = get_pos_color(pos_type);
		if ((!((int)map_pos.start.y % (int)TILESIZE) || !((int)map_pos.start.x
					% (int)TILESIZE)) && pos_type == e_wall)
			color = 0x000000;
	}
	return (color);
}

void	map_game(void)
{
	t_map_data	data;

	init_map_pos(&data.map_pos, &data.start);
	while (data.map_pos.start.y < data.map_pos.end.y)
	{
		data.map_pos.start.x = data.start.x;
		data.y = round(data.map_pos.start.y - data.start.y);
		while (data.map_pos.start.x < data.map_pos.end.x)
		{
			data.x = round(data.map_pos.start.x - data.start.x);
			data.pos_type = check_pos(data.map_pos.start.x,
					data.map_pos.start.y);
			data.color = get_color(data.x, data.y, data.map_pos, data.pos_type);
			my_mlx_put_pixel(&g_vars()->map_img, data.x, data.y, data.color);
			data.map_pos.start.x++;
		}
		data.map_pos.start.y++;
	}
	draw_circle(&g_vars()->map_img, (t_point){g_vars()->player.pixl_pos.x
		- data.start.x, g_vars()->player.pixl_pos.y - data.start.y}, 5,
		0xff5555);
	draw_player_dir(g_vars()->player.angle + (FOV / 2), 30, data.start);
	draw_player_dir(g_vars()->player.angle - (FOV / 2), 30, data.start);
}
