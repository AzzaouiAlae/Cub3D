/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:03:02 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/03 10:30:29 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

int	darkness_effect(int color, double dist)
{
	t_color	*c;
	int		res;

	c = (t_color *)(&color);
	res = (255.0 / (double)DARKNESS) * dist;
	if (res > c->b)
		c->b = 0;
	else
		c->b -= res;
	if (res > c->r)
		c->r = 0;
	else
		c->r -= res;
	if (res > c->g)
		c->g = 0;
	else
		c->g -= res;
	return (c->r << 16 | c->g << 8 | c->b);
}

int	darkness_effect_ceil(int color, double dist)
{
	t_color	*c;
	int		res;

	c = (t_color *)(&color);
	res = (255.0 / (540 + C_F_DARKNES)) * dist;
	if (res > c->b)
		c->b = 0;
	else
		c->b -= res;
	if (res > c->r)
		c->r = 0;
	else
		c->r -= res;
	if (res > c->g)
		c->g = 0;
	else
		c->g -= res;
	return (c->r << 16 | c->g << 8 | c->b);
}

int	darkness_effect_floor(int color, double dist)
{
	t_color	*c;
	int		res;

	c = (t_color *)(&color);
	res = (255.0 / (540 + C_F_DARKNES)) * (g_vars()->height - dist);
	if (res > c->b)
		c->b = 0;
	else
		c->b -= res;
	if (res > c->r)
		c->r = 0;
	else
		c->r -= res;
	if (res > c->g)
		c->g = 0;
	else
		c->g -= res;
	return (c->r << 16 | c->g << 8 | c->b);
}

void	draw_line(t_draw_line data)
{
	int		i;
	int		color;
	double	ofst;
	t_data	*img;

	i = 0;
	img = get_img(data.p.side, data.p.type);
	ofst = (img->img_height / data.orginal_l);
	draw_ceil(data);
	while (i < data.length && data.y + i < g_vars()->height)
	{
		color = my_mlx_get_pixel(img, round(data.img_start.x),
				round(data.img_start.y));
		color = darkness_effect(color, data.p.distance);
		my_mlx_put_pixel(&g_vars()->win_img, data.x, data.y + i, color);
		data.img_start.y += ofst;
		i++;
	}
	draw_floor(data, i);
}

void	render_walls(t_end_point p, int i)
{
	t_draw_line	data;
	t_data		*img;
	double		tile_x;

	img = get_img(p.side, p.type);
	data.length = (g_vars()->height * TILESIZE) / p.distance;
	tile_x = p.end.y - floor(p.end.y / TILESIZE) * TILESIZE;
	if (p.side == north || p.side == south)
		tile_x = p.end.x - floor(p.end.x / TILESIZE) * TILESIZE;
	if (p.side == north || p.side == west)
		tile_x = TILESIZE - tile_x;
	data.img_start.x = ((double)img->img_width / TILESIZE) * tile_x;
	data.img_start.y = (g_vars()->height - data.length) / 2;
	if (data.img_start.y > 0)
		data.img_start.y = 0;
	else
		data.img_start.y = fabs(data.img_start.y) * ((double)img->img_height
				/ (double)data.length);
	if (data.length > g_vars()->height)
		data.length = g_vars()->height;
	data.x = i;
	data.y = (g_vars()->height - data.length) / 2;
	data.orginal_l = (g_vars()->height * (double)TILESIZE) / p.distance;
	data.p = p;
	draw_line(data);
}
