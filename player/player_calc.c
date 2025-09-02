/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:54:27 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:55:27 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_game/map_game.h"
#include "player.h"

double	ph_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

void	draw_circle(t_data *img, t_point p, int r, int color)
{
	t_line	circle_bor;
	double	x;

	circle_bor.start.x = p.x - r;
	circle_bor.start.y = p.y - r;
	circle_bor.end.x = p.x + r;
	circle_bor.end.y = p.y + r;
	while (circle_bor.start.y <= circle_bor.end.y)
	{
		x = circle_bor.start.x;
		while (x <= circle_bor.end.x)
		{
			if (ph_distance(p, (t_point){x, circle_bor.start.y}) <= r)
				my_mlx_put_pixel(img, x, circle_bor.start.y, color);
			x++;
		}
		circle_bor.start.y++;
	}
}

void	calculate_player_speed(void)
{
	g_vars()->player.move_speed = (PLAYER_SPEED / (1000 * 1000))
	* (g_vars()->time - g_vars()->old_time);
	if (g_vars()->player.move_speed > PLAYER_SPEED)
		g_vars()->player.move_speed = PLAYER_SPEED;
	g_vars()->player.turn_speed = (ANGLE_SPEED / (1000 * 1000) * (g_vars()->time
			- g_vars()->old_time));
	if (g_vars()->player.turn_speed > ANGLE_SPEED)
		g_vars()->player.turn_speed = ANGLE_SPEED;
}

void	draw_player_dir(double angle, double dir_dist, t_point start)
{
	t_point	dir;
	t_point	pos;

	normalize_angle(&angle);
	dir.x = cos(angle * M_PI / 180);
	dir.y = -sin(angle * M_PI / 180);
	pos.x = dir.x + g_vars()->player.pixl_pos.x;
	pos.y = dir.y + g_vars()->player.pixl_pos.y;
	while (ph_distance(g_vars()->player.pixl_pos, pos) < dir_dist)
	{
		my_mlx_put_pixel(&g_vars()->map_img, pos.x - start.x, pos.y - start.y,
			0xff0000);
		pos.x += dir.x;
		pos.y += dir.y;
	}
}
