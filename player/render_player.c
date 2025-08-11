#include "player.h"
#include "../ray_casting/ray_casting.h"
#include "../min_map/min_map.h"

int get_color(t_side side)
{
	if (side == east)
		return 0xff0000;
	if (side == west)
		return 0x00ff00;
	if (side == north)
		return 0x0000ff;
	return 0xffffff;
}

void draw_line(int x, int y, int l, t_side side)
{
	int i;

	i = 0;
	while(i < l)
	{
		my_mlx_put_pixel(&g_win_img, x, y + i, get_color(side));
		i++;
	}
}

void render_walls(t_end_point p, int i)
{
    int length = (g_height * M_M_TIAL_SIZE) / p.distance;
    if (length > g_height)
        length = g_height;
    draw_line(i, (g_height - length) / 2, length, p.side);
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
		render_walls(p, i);
		put_pixel_min_map(p.point.x, p.point.y, 0xff00ff);
		view_start -= FOV / g_width;
		i++;
	}
	render_line_angle(g_player.angle - FOV / 2, 20, 0x7777ff);
	render_line_angle(g_player.angle + FOV / 2, 20, 0x7777ff);
	// render_line_angle(g_player.angle , 20, 0x7777ff);
	// render_player_angle(g_player.angle);
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
