#include "cub3d.h"
#include "ray_casting/ray_casting.h"

bool	is_posible_move(int x, int y)
{
	int		row;
	int		col;
	t_str	**grid;

	col = y / M_M_TIAL_SIZE;
	row = x / M_M_TIAL_SIZE;
	grid = g_map->content;
	g_player.map_pos.y = g_player.pos.y / M_M_TIAL_SIZE;
	g_player.map_pos.x = g_player.pos.x / M_M_TIAL_SIZE;
	if (g_map->count <= col || col < 0 || grid[col]->count <= row || row < 0)
		return (false);
	if (grid[col]->content[row] == '1')
		return (false);
	return (true);
}

bool is_intersection(t_point point, float angle)
{
	t_point offset;
	t_end_point p1;
	t_end_point p2;

	p1 = ray_cast_dist(point, &offset, angle + 90, M_M_TIAL_SIZE / 2);
	p2 = ray_cast_dist(point, &offset, angle - 90, M_M_TIAL_SIZE / 2);
	if(!is_posible_move(p1.point.x, p1.point.y) &&
		!is_posible_move(p2.point.x, p2.point.y))
		return true;
	return false;
}

