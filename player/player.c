#include "player.h"
#include "../ray_casting/ray_casting.h"

bool is_valid_player_move(t_point p)
{
	int x;
	int y;

	x = p.x;
	y = p.y;
	if (!is_posible_move(x, y))
		return false;
	if (!is_posible_move(x + 1, y))
		return false;
	if (!is_posible_move(x, y + 1))
		return false;
	if (!is_posible_move(x - 2, y))
		return false;
	if (!is_posible_move(x, y - 2))
		return false;
	if (!is_posible_move(x + 1, y + 1))
		return false;
	if (!is_posible_move(x - 2, y - 2))
		return false;
	return true;
}

void player_step(bool *should_break, t_point *end, t_end_point p)
{
	*should_break = true;
	if (is_valid_player_move((t_point){end->x, g_player.pos.y}) && g_player.pos.x != end->x)
	{
		*should_break = false;
		g_player.pos.x = end->x;
	}
	if (is_valid_player_move((t_point){g_player.pos.x, end->y}) && g_player.pos.y != end->y)
	{
		*should_break = false;
		g_player.pos.y = end->y;
	}
	*end = calc_align(g_player.pos, p.point, 0.5);
}

void move_player_by_angle(float angle)
{
	t_end_point p;
	t_point end;
	t_point old_player_pos;
	bool should_break = false;
	t_point ofset;
	t_end_point point;
	t_str	**grid;

	grid = g_map->content;
	should_break = false;
	old_player_pos.x = g_player.pos.x;
	old_player_pos.y = g_player.pos.y;
	p = ray_cast(angle);
	if (is_door(p.point.x, p.point.y, INFINITY) && grid[g_door_info.col]->content[g_door_info.row] != 'D')
	{
		if (p.distance < 3)
		{
			point = ray_cast_dist(g_player.pos, &ofset, angle, M_M_TIAL_SIZE);
			point.point.x += ofset.x * 1.05;
			point.point.y += ofset.y * 1.05;
			if (point.side == east || point.side == south)
				point.point.y = floor(point.point.y / M_M_TIAL_SIZE) * M_M_TIAL_SIZE  + (M_M_TIAL_SIZE / 2);
			else
				point.point.x = floor(point.point.x / M_M_TIAL_SIZE) * M_M_TIAL_SIZE + (M_M_TIAL_SIZE / 2);
			g_player.pos.x = point.point.x;
			g_player.pos.y = point.point.y;
		}
	}
	else if (p.distance < 0.5)
		return;
	end = calc_align(g_player.pos, p.point, 0.5);
	while (distance(old_player_pos, g_player.pos) < PLAYER_SPEED && !should_break)
	{
		player_step(&should_break, &end, p);
	}
}

void	move_player(void)
{
	if (g_keys.w)
		move_player_by_angle(g_player.angle);
	if (g_keys.a )
		move_player_by_angle(g_player.angle + 90);
	if (g_keys.d)
		move_player_by_angle(g_player.angle - 90);
	if (g_keys.s )
		move_player_by_angle(g_player.angle - 180);
	if (g_keys.right)
		g_player.angle -= ANGLE_SPEED;
	if (g_keys.left)
		g_player.angle += ANGLE_SPEED;
	g_player.angle += 360;
	g_player.angle = (int)g_player.angle % 360;
}
