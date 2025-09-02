#include "map_game.h"
#include "../raycasting/raycasting.h"
#include "../player/player.h"

void	init_map_pos(t_line *map_pos, t_point *start)
{
	map_pos->start.x = g_player.pixl_pos.x - (MAP_W / 2);
	map_pos->start.y = g_player.pixl_pos.y - (MAP_HEIGHT / 2);
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

	the_map = g_map->content;
	row = y / TILESIZE;
	col = x / TILESIZE;
	if (row < 0 || g_map->count <= row || y < 0)
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
	t_line		map_pos;
	t_point		start;
	t_pos_type	pos_type;
	int			y;
	int			x;
	int			color;

	init_map_pos(&map_pos, &start);
	while (map_pos.start.y < map_pos.end.y)
	{
		map_pos.start.x = start.x;
		y = round(map_pos.start.y - start.y);
		while (map_pos.start.x < map_pos.end.x)
		{
			x = round(map_pos.start.x - start.x);
			pos_type = check_pos(map_pos.start.x, map_pos.start.y);
			color = get_color(x, y, map_pos, pos_type);
			my_mlx_put_pixel(&g_map_img, x, y, color);
			map_pos.start.x++;
		}
		map_pos.start.y++;
	}
	draw_circle(&g_map_img, (t_point){g_player.pixl_pos.x - start.x,
		g_player.pixl_pos.y - start.y}, 5, 0xff5555);
	draw_player_dir(g_player.angle + (FOV / 2), 30, start);
	draw_player_dir(g_player.angle - (FOV / 2), 30, start);
}
