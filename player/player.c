#include "player.h"

double ph_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

void draw_circle(t_data *img, t_point p, int r, int color)
{
	t_line circle_bor;
	double x;

	circle_bor.start.x = p.x - r;
	circle_bor.start.y = p.y - r;
	circle_bor.end.x = p.x + r;
	circle_bor.end.y = p.y + r;
	while(circle_bor.start.y <= circle_bor.end.y)
	{
		x = circle_bor.start.x;
		while(x <= circle_bor.end.x)
		{
			if (ph_distance(p, (t_point){x, circle_bor.start.y}) <= r)
				my_mlx_put_pixel(img, x, circle_bor.start.y, color);
			x++;
		}
		circle_bor.start.y++;
	}
}

void calculate_player_speed()
{
	g_player.move_speed = (PLAYER_SPEED / (1000 * 1000)) * (g_time - g_old_time);
	if (g_player.move_speed > PLAYER_SPEED)
		g_player.move_speed = PLAYER_SPEED;
	g_player.turn_speed = (ANGLE_SPEED / (1000 * 1000) * (g_time - g_old_time));
	if (g_player.turn_speed > ANGLE_SPEED)
		g_player.turn_speed = ANGLE_SPEED;
}

bool is_valid_move(int x, int y)
{
	return check_pos(g_player.pixl_pos.x + x, g_player.pixl_pos.y + y) == e_empty;
}

void move_player()
{
	g_old_time = g_time;
	g_time = get_curr_time();
	calculate_player_speed();
	if (g_keys.w && is_valid_move(0, -(g_player.move_speed + SAFETY)))
	{
			g_player.pixl_pos.y -= g_player.move_speed;
	}
	if (g_keys.d && is_valid_move(g_player.move_speed + SAFETY, 0))
	{
		g_player.pixl_pos.x += g_player.move_speed;
	}
	if (g_keys.a && is_valid_move(-(g_player.move_speed + SAFETY), 0))
	{
		g_player.pixl_pos.x -= g_player.move_speed;
	}
	if (g_keys.s && is_valid_move(0, g_player.move_speed + SAFETY))
	{
		g_player.pixl_pos.y += g_player.move_speed;
	}
}

/*
time;
old_time;
sec
player_speed

(sec / (time - old_time)) / player_speed;

*/