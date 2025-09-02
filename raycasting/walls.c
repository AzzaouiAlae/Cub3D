/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:03:02 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 18:03:18 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

int	darkness_effect(int color, double dist)
{
	t_color	c;
	int		res;

	c = *((t_color *)(&color));
	res = (255.0 / (double)DARKNESS) * dist;
	if (res > c.b)
		c.b = 0;
	else
		c.b -= res;
	if (res > c.r)
		c.r = 0;
	else
		c.r -= res;
	if (res > c.g)
		c.g = 0;
	else
		c.g -= res;
	return (*(int *)&c);
}

int	darkness_effect_ceil(int color, double dist)
{
	t_color	c;
	int		res;

	c = *((t_color *)(&color));
	res = (255.0 / (540 + C_F_DARKNES)) * dist;
	if (res > c.b)
		c.b = 0;
	else
		c.b -= res;
	if (res > c.r)
		c.r = 0;
	else
		c.r -= res;
	if (res > c.g)
		c.g = 0;
	else
		c.g -= res;
	return (*(int *)&c);
}

int	darkness_effect_floor(int color, double dist)
{
	t_color	c;
	int		res;

	c = *((t_color *)(&color));
	res = (255.0 / (540 + C_F_DARKNES)) * (g_height - dist);
	if (res > c.b)
		c.b = 0;
	else
		c.b -= res;
	if (res > c.r)
		c.r = 0;
	else
		c.r -= res;
	if (res > c.g)
		c.g = 0;
	else
		c.g -= res;
	return (*(int *)&c);
}

void	draw_line(int x, int y, int l, t_point img_start, double orginal_l,
		t_end_point p)
{
	int		i;
	int		color;
	double	ofst;
	t_data	*img;

	i = 0;
	img = get_img(p.side, p.type);
	ofst = (img->img_height / orginal_l);
	while (i < y)
	{
		color = darkness_effect_ceil(g_info.ceil_color, i);
		my_mlx_put_pixel(&g_win_img, x, i, color);
		i++;
	}
	i = 0;
	while (i < l && y + i < g_height)
	{
		color = my_mlx_get_pixel(img, round(img_start.x), round(img_start.y));
		color = darkness_effect(color, p.distance);
		my_mlx_put_pixel(&g_win_img, x, y + i, color);
		img_start.y += ofst;
		i++;
	}
	y += i;
	while (y < g_height)
	{
		color = darkness_effect_floor(g_info.floor_color, y);
		my_mlx_put_pixel(&g_win_img, x, y, color);
		y++;
	}
}

void	render_walls(t_end_point p, int i)
{
	t_point	img_start;
	t_data	*img;
	int		length;
	double	tile_x;

	img = get_img(p.side, p.type);
	length = (g_height * TILESIZE) / p.distance;
	tile_x = p.end.y - floor(p.end.y / TILESIZE) * TILESIZE;
	if (p.side == north || p.side == south)
		tile_x = p.end.x - floor(p.end.x / TILESIZE) * TILESIZE;
	if (p.side == north || p.side == west)
		tile_x = TILESIZE - tile_x;
	img_start.x = ((double)img->img_width / TILESIZE) * tile_x;
	img_start.y = (g_height - length) / 2;
	if (img_start.y > 0)
		img_start.y = 0;
	else
		img_start.y = fabs(img_start.y) * ((double)img->img_height
				/ (double)length);
	if (length > g_height)
		length = g_height;
	draw_line(i, (g_height - length) / 2, length, img_start, (g_height
			* (double)TILESIZE) / p.distance, p);
}
