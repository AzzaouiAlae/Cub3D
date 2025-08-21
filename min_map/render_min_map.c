#include "min_map.h"

void	render_mini_map_border()
{
    int brd;
    int y;
	int	x;

	y = 0;
    brd = M_M_BORDER_SIZE;
	while (y < M_M_H)
	{
		x = 0;
		while (x < M_M_W)
		{
			if (in_range(0, 0 + brd - 1, x) || in_range(M_M_W - brd, M_M_W, x) 
                || in_range(0, 0 + brd - 1, y) || in_range(M_M_H - brd, M_M_H, y) )
				my_mlx_put_pixel(&g_min_map_img, x, y, 0xffffff);
			x++;
		}
		y++;	
	}
}

void	init_out_border(t_line *out_border)
{
	out_border->start = (t_point){M_M_MARGIN_X, M_M_MARGIN_Y};
	out_border->end = (t_point){M_M_MARGIN_X + M_M_W, M_M_MARGIN_Y + M_M_H};
}

void	render_pos(t_line line, float x, float y)
{
	int		row;
	int		col;
	int		color;
	t_str	**grid;
	t_point rend;

	if (y < 0 || x < 0)
		return;
	col = y / M_M_TIAL_SIZE;
	row = x / M_M_TIAL_SIZE;
	grid = g_map->content;
	if (g_map->count <= col || grid[col]->count <= row )
		return ;
	if (grid[col]->content[row] == '1' || 
		grid[col]->content[row] == 'D' || 
		grid[col]->content[row] == 'd')
	{
		if (grid[col]->content[row] == '1')
			color = 0x5555ff;
		else
			color = 0xeeeeee;
		if ((int)x % (int)M_M_TIAL_SIZE == 0 || (int)y % (int)M_M_TIAL_SIZE == 0)
			color = 0xffffff;
		rend.x = x + M_M_BORDER_SIZE - line.start.x;
		rend.y = y + M_M_BORDER_SIZE - line.start.y;
		my_mlx_put_pixel(&g_min_map_img, round(rend.x), round(rend.y), color);
	}
}

void	render_mini_map(void)
{
	t_line	border;
	t_line out_border;
	float	x;
	float	y;
	
	init_out_border(&out_border);
    clear_img();
    init_mini_map_border(&border);
    render_mini_map_border();
	y = border.start.y;
	while (y <= border.end.y)
	{
		x = border.start.x;
		while (x <= border.end.x)
		{
			render_pos(border, x, y);
			x++;
		}
		y++;
	}
}
