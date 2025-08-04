#include "min_map.h"

void init_mini_map_border(t_line	*border)
{
	border->start.x = g_player.pos.x - ((float)(M_M_W - M_M_BORDER_SIZE * 2) / 2);
	border->start.y = g_player.pos.y - ((float)(M_M_H - M_M_BORDER_SIZE * 2) / 2);
	border->end.x = border->start.x + M_M_W - M_M_BORDER_SIZE * 2;
	border->end.y = border->start.y + M_M_H - M_M_BORDER_SIZE * 2;
}

void put_pixel_min_map(float x, float y, int color)
{
	t_line border;
	t_point rend;

	init_mini_map_border(&border);
	rend.x = x - border.start.x + M_M_MARGIN_X;
	rend.y = y - border.start.y + M_M_MARGIN_Y;
	if (is_in_mini_map(rend.x, rend.y))
		my_mlx_put_pixel(&g_win_img, round(rend.x), round(rend.y), color);
}

void	clear_img(t_line area)
{
	int	x;
	int	color;

	color = 0;
	while (area.start.y <= area.end.y)
	{
		x = area.start.x;
		while (x <= area.end.x)
		{
			my_mlx_put_pixel(&g_win_img, x, area.start.y, color);
			x++;
		}
		area.start.y++;
	}
}

bool is_in_mini_map(int x, int y)
{
	if (!(x < M_M_MARGIN_X + M_M_W))
		return false;
	if (!(y < M_M_MARGIN_Y + M_M_H ))
		return false;
	if (!(x >= M_M_MARGIN_X))
		return false;
	if (!(y >= M_M_MARGIN_Y))
		return false;
	return true;
}
