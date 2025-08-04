#include "player.h"
#include "../ray_casting/ray_casting.h"

void move_player_by_angle(float angle)
{
	t_end_point p;
	t_point ofst;

	p = ray_cast_dist(g_player.pos, &ofst, angle, PLAYER_SPEED);
	if(is_posible_move(p.point.x + ofst.x * 2, p.point.y + ofst.y * 2))
	{
		if (is_intersection(p.point, angle))
			return;
		g_player.pos.x = p.point.x;
		g_player.pos.y = p.point.y;
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
}

