/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:51:37 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 18:03:35 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

t_door		g_door_info;

void	save_door_info(int x, int y, double dist)
{
	if (dist < g_door_info.dist || !g_door_info.dist)
	{
		g_door_info.col = x / TILESIZE;
		g_door_info.row = y / TILESIZE;
		g_door_info.dist = dist;
	}
}

void	reset_door_info(void)
{
	g_door_info.col = 0;
	g_door_info.row = 0;
	g_door_info.dist = 0;
}

void	check_door(t_point p, double dist)
{
	t_pos_type	res;

	res = check_pos(p.x, p.y);
	if (res == e_opened_gate || res == e_closed_gate)
		save_door_info(p.x, p.y, dist);
}

t_side	get_side(t_point p, t_point start, char inter, t_side *type)
{
	t_pos_type	res;

	*type = north;
	res = check_pos(p.x, p.y);
	if (res == e_opened_gate)
		*type = open_door;
	else if (res == e_closed_gate)
		*type = close_door;
	if (inter == 'x')
	{
		if (p.x > start.x)
			return (east);
		else
			return (west);
	}
	else if (inter == 'y')
	{
		if (p.y < start.y)
			return (south);
		else
			return (north);
	}
	return (north);
}

t_end_point	x_intersections(t_point start, double angle)
{
	t_end_point	p;

	if (!(in_range(0, 90, angle) || in_range(270, 360, angle)))
	{
		p.end.x = floor(start.x / TILESIZE) * TILESIZE - 0.000000001;
		p.delta_dist.x = -TILESIZE;
	}
	else
	{
		p.end.x = floor(start.x / TILESIZE) * TILESIZE + TILESIZE;
		p.delta_dist.x = TILESIZE;
	}
	p.end.y = start.y + fabs(start.x - p.end.x) * my_tan(angle, 'x');
	p.delta_dist.y = TILESIZE * my_tan(angle, 'x');
	while (is_valid_ray(p.end.x, p.end.y))
	{
		p.end.x += p.delta_dist.x;
		p.end.y += p.delta_dist.y;
	}
	p.distance = ph_distance(start, p.end);
	p.side = get_side(p.end, start, 'x', &p.type);
	return (p);
}

t_end_point	y_intersections(t_point start, double angle)
{
	t_end_point	p;

	if (in_range(0, 180, angle))
	{
		p.end.y = floor(start.y / TILESIZE) * TILESIZE - 0.000000001;
		p.delta_dist.y = -TILESIZE;
	}
	else
	{
		p.end.y = floor(start.y / TILESIZE) * TILESIZE + TILESIZE;
		p.delta_dist.y = TILESIZE;
	}
	p.end.x = start.x + fabs(start.y - p.end.y) / my_tan(angle, 'y');
	p.delta_dist.x = TILESIZE / my_tan(angle, 'y');
	while (is_valid_ray(p.end.x, p.end.y))
	{
		p.end.x += p.delta_dist.x;
		p.end.y += p.delta_dist.y;
	}
	p.distance = ph_distance(start, p.end);
	p.side = get_side(p.end, start, 'y', &p.type);
	return (p);
}

t_end_point	raycaster(t_point start, double angle)
{
	t_end_point	point_x;
	t_end_point	point_y;

	point_x = x_intersections(start, angle);
	point_y = y_intersections(start, angle);
	if (point_x.distance < point_y.distance)
		return (point_x);
	return (point_y);
}

t_data	*get_img(t_side side, t_side type)
{
	if (type == open_door)
		return (get_open_door_img());
	if (type == close_door)
		return (get_close_door_img());
	if (side == east)
		return (get_east_img());
	if (side == west)
		return (get_west_img());
	if (side == north)
		return (get_north_img());
	return (get_south_img());
}

void draw_player_dir(double angle, double dir_dist, t_point	start)
{
	t_point dir;
	t_point pos;

	normalize_angle(&angle);
	dir.x = cos(angle * M_PI / 180);
	dir.y = -sin(angle * M_PI / 180);
	pos.x = dir.x + g_player.pixl_pos.x;
	pos.y = dir.y + g_player.pixl_pos.y;
	while (ph_distance(g_player.pixl_pos, pos) < dir_dist)
	{
		my_mlx_put_pixel(&g_map_img, pos.x - start.x, pos.y - start.y,
			0xff0000);
		pos.x += dir.x;
		pos.y += dir.y;
	}
}

void	cast_all_rays(void)
{
	double		dpr;
	double		angle;
	double		real_alpha;
	t_end_point	p;
	int			i;
	t_line		map_pos;
	t_point		start;

	i = 0;
	dpr = FOV / g_width;
	angle = g_player.angle + (FOV / 2);
	real_alpha = 30;
	init_map_pos(&map_pos, &start);
	reset_door_info();
	while (i < g_width)
	{
		normalize_angle(&angle);
		p = raycaster(g_player.pixl_pos, angle);
		check_door(p.end, p.distance);
		p.distance *= my_cos(real_alpha);
		render_walls(p, i);
		angle -= dpr;
		real_alpha -= dpr;
		i++;
	}
}
