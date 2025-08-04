#include "min_map.h"

void	render_mini_map_border()
{
    t_point s;
    t_point e;
    int brd;
    int y;
	int	x;

    s = (t_point){M_M_MARGIN_X, M_M_MARGIN_Y};
    e = (t_point){M_M_MARGIN_X + M_M_W, M_M_MARGIN_Y + M_M_H};
    brd = M_M_BORDER_SIZE;
    y = s.y;
	while (y <= e.y)
	{
		x = s.x;
		while (x <= e.x)
		{
			if (in_range(s.x, s.x + brd - 1, x) || in_range(e.x - brd + 1, e.x, x) 
                || in_range(s.y, s.y + brd - 1, y) || in_range(e.y - brd + 1, e.y, y) )
				my_mlx_put_pixel(&g_win_img, x, y, 0xffffff);
			x++;
		}
		y++;
	}
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
	if (grid[col]->content[row] == '1')
	{
		color = 0x5555ff;
		if ((int)x % M_M_TIAL_SIZE == 0 || (int)y % M_M_TIAL_SIZE == 0)
			color = 0xffffff;
		rend.x = x + M_M_MARGIN_X + M_M_BORDER_SIZE - line.start.x;
		rend.y = y + M_M_MARGIN_Y + M_M_BORDER_SIZE - line.start.y;
		my_mlx_put_pixel(&g_win_img, rend.x, rend.y, color);
	}
}

void	render_mini_map(void)
{
	t_line	border;
	float	x;
	float	y;
	
    clear_img((t_line){(t_point){M_M_MARGIN_X, M_M_MARGIN_Y},
		(t_point){M_M_MARGIN_X + M_M_W, M_M_MARGIN_Y + M_M_H}});
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
