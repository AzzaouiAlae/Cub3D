/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:51:37 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 22:54:01 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

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

void	cast_all_rays(void)
{
	t_raycaster	data;

	data.i = 0;
	data.dpr = FOV / g_vars()->width;
	data.angle = g_vars()->player.angle + (FOV / 2);
	data.real_alpha = 30;
	init_map_pos(&data.map_pos, &data.start);
	reset_door_info();
	while (data.i < g_vars()->width)
	{
		normalize_angle(&data.angle);
		data.p = raycaster(g_vars()->player.pixl_pos, data.angle);
		check_door(data.p.end, data.p.distance);
		data.p.distance *= my_cos(data.real_alpha);
		render_walls(data.p, data.i);
		data.angle -= data.dpr;
		data.real_alpha -= data.dpr;
		data.i++;
	}
}
