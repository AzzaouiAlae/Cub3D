#include "player.h"
#include "../ray_casting/ray_casting.h"
#include "../min_map/min_map.h"

void player_render()
{
	t_line	border;
	float view_start;

	move_player();
	init_mini_map_border(&border);
	draw_player_cercl(border, g_player.pos.x, g_player.pos.y, (int[]){0, 1, 2, 1, 0});
	view_start = g_player.angle + FOV / 2;
	while (view_start > g_player.angle - FOV / 2) 
	{
		render_player_angle(view_start);
		view_start -= (float)FOV / (float)g_width;
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

void render_player_angle(float angle)
{
	t_end_point p;
	
	p = ray_cast(angle);
	p.point.x += 1;
	p.point.y += 1;
	put_pixel_min_map(p.point.x, p.point.y, 0xff00ff);
	p.distance = distance(p.point, g_player.pos);
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
			rend.x = x_start - border.start.x + M_M_MARGIN_X;
			rend.y = y - 2 + i - border.start.y + M_M_MARGIN_Y;
			my_mlx_put_pixel(&g_win_img, rend.x, rend.y, color);
			x_start++;
		}
		i++;
	}
}
