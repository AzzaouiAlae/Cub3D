#include "min_map.h"

void init_mini_map_border(t_line	*border)
{
	border->start.x = g_player.pos.x - ((M_M_W - M_M_BORDER_SIZE * 2) / 2);
	border->start.y = g_player.pos.y - ((M_M_H - M_M_BORDER_SIZE * 2) / 2);
	border->end.x = border->start.x + M_M_W - M_M_BORDER_SIZE * 2;
	border->end.y = border->start.y + M_M_H - M_M_BORDER_SIZE * 2;
}

void put_pixel_min_map(float x, float y, int color)
{
	t_line border;
	t_point rend;

	init_mini_map_border(&border);
	rend.x = x - border.start.x + M_M_BORDER_SIZE;
	rend.y = y - border.start.y + M_M_BORDER_SIZE;
	if (is_in_mini_map(rend.x, rend.y))
		my_mlx_put_pixel(&g_min_map_img, round(rend.x), round(rend.y), color);
}

void	clear_img()
{
	int	x;
	int y;
	int	color;

	color = 0;
	y = 0;
	while (y < M_M_H)
	{
		x = 0;
		while (x < M_M_W)
		{
			my_mlx_put_pixel(&g_min_map_img, x, y, color);
			x++;
		}
		y++;
	}
}

bool is_in_mini_map(int x, int y)
{
	if (!(x < M_M_W))
		return false;
	if (!(y < M_M_H))
		return false;
	if (!(x >= 0))
		return false;
	if (!(y >= 0))
		return false;
	return true;
}
