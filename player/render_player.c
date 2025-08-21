#include "player.h"
#include "../ray_casting/ray_casting.h"
#include "../min_map/min_map.h"

t_data *get_image(t_side side)
{
	if (side == east)
		return g_info.east;
	if (side == west)
		return g_info.west;
	if (side == north)
		return g_info.south;
	return g_info.south;
}

void draw_line(int x, int y, int l, t_point img_start, double orginal_l, t_end_point p)
{
	int i;
	int color;
	double ofst;
	t_data *img;

	i = 0;
	ofst = (g_info.east->img_height / orginal_l);
	img = get_image(p.side);
	while(i < l && y + i < g_height)
	{
		color = my_mlx_get_pixel(img, round(img_start.x), round(img_start.y));
		my_mlx_put_pixel(&g_win_img, x, y + i, color);
		img_start.y += ofst;
		i++;
	}
}

void render_walls(t_end_point p, int i)
{
    t_point img_start;

    int length = (g_height * M_M_TIAL_SIZE) / p.distance;
	img_start.x = (g_info.east->img_width / M_M_TIAL_SIZE) * p.point.y; // or p.point.y
	if (p.side == north || p.side == south)
		img_start.x = (g_info.east->img_width / M_M_TIAL_SIZE) * p.point.x; // or p.point.y
	img_start.y = (g_height - length) / 2;
	if (img_start.y > 0)
		img_start.y = 0;
	else
		img_start.y = fabs(img_start.y) * ((double)g_info.east->img_height / (double)length);
    if (length > g_height)
        length = g_height;
    draw_line(i, (g_height - length) / 2, length, img_start, (g_height * M_M_TIAL_SIZE) / p.distance, p);
}

double my_cos(float alpha)
{
	return (cos(alpha * (float)(M_PI / 180)));
}

void player_render()
{
	t_line	border;
	float view_start;
	int i;
	t_end_point p;

	i = 0;
	move_player();
	init_mini_map_border(&border);
	draw_player_cercl(border, g_player.pos.x, g_player.pos.y, (int[]){0, 1, 2, 1, 0});
	view_start = g_player.angle + FOV / 2;
	while (i < g_width)
	{
		if (view_start < 0)
			view_start += 360;
		if (view_start > 360)
			view_start -= 360;
		p = render_player_angle(view_start);
		p.distance *= my_cos((FOV / 2 - ((FOV / g_width) * i)));
		render_walls(p, i);
		put_pixel_min_map(p.point.x, p.point.y, 0xff00ff);
		view_start -= FOV / g_width;
		i++;
	}
	render_line_angle(g_player.angle - FOV / 2, 20, 0x7777ff);
	render_line_angle(g_player.angle + FOV / 2, 20, 0x7777ff);
}

void render_line_angle(float angle, float dist, int	color)
{
	t_point offset;
	t_end_point p;

	p = ray_cast_dist(g_player.pos, &offset, angle, 1);
	while(is_posible_move(p.point.x, p.point.y)
		&& distance(p.point, g_player.pos) < dist)
	{
		put_pixel_min_map(p.point.x, p.point.y, color);
		if (!is_posible_move(p.point.x + offset.x, p.point.y)
			&& !is_posible_move(p.point.x, p.point.y + offset.y))
			return;
		p.point.x += offset.x;
		p.point.y += offset.y;
	}
}

t_end_point render_player_angle(float angle)
{
	t_end_point p;

	p = ray_cast(angle);
	p.distance = distance(p.point, g_player.pos);
	return p;
}

void	draw_player_cercl(t_line border, float x, float y, int x_ranges[])
{
	int	i;
	int	y_max;
	int	x_start;
	int	color;
	t_point rend;

	i = 0;
	y_max = y + 2;
	color = 0xff0000;
	while (y_max >= y - 2 + i)
	{
		x_start = x - x_ranges[i];
		while (x_start <= x + x_ranges[i])
		{
			rend.x = x_start - border.start.x +  M_M_BORDER_SIZE;
			rend.y = y - 2 + i - border.start.y + M_M_BORDER_SIZE;
			my_mlx_put_pixel(&g_min_map_img, round(rend.x), round(rend.y), color);
			x_start++;
		}
		i++;
	}
}
