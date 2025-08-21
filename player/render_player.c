#include "player.h"
#include "../ray_casting/ray_casting.h"
#include "../min_map/min_map.h"

t_door g_door_info;

t_data *get_image(t_side side)
{
	if (side == east)
		return g_info.east;
	if (side == west)
		return g_info.west;
	if (side == north)
		return g_info.south;
	if (side == open_door)
		return g_info.open_door;
	if (side == close_door)
		return g_info.close_door;
	return g_info.south;
}

void draw_line(int x, int y, int l, t_point img_start, double orginal_l, t_end_point p)
{
	int i;
	int color;
	double ofst;
	t_data *img;

	i = 0;
	img = get_image(p.side);
	ofst = (img->img_height / orginal_l);
	while (i < y)
	{
		my_mlx_put_pixel(&g_win_img, x, i, g_info.ceil_color);
		i++;
	}
	i = 0;
	while(i < l && y + i < g_height)
	{
		color = my_mlx_get_pixel(img, round(img_start.x), round(img_start.y));
		my_mlx_put_pixel(&g_win_img, x, y + i, color);
		img_start.y += ofst;
		i++;
	}
	y += i;
	while (y < g_height)
	{
		my_mlx_put_pixel(&g_win_img, x, y, g_info.floor_color);
		y++;
	}
}

void render_walls(t_end_point p, int i)
{
    t_point img_start;
	t_data *img;

	img = get_image(p.side);
    int length = (g_height * M_M_TIAL_SIZE) / p.distance;
	double real_x = p.point.y - floor(p.point.y / M_M_TIAL_SIZE) * M_M_TIAL_SIZE; 
	if (p.side == north || p.side == south)
		real_x = p.point.x - floor(p.point.x / M_M_TIAL_SIZE) * M_M_TIAL_SIZE; 
	img_start.x = (img->img_width / M_M_TIAL_SIZE) * real_x;
	img_start.y = (g_height - length) / 2;
	if (img_start.y > 0)
		img_start.y = 0;
	else 
		img_start.y = fabs(img_start.y) * ((double)img->img_height / (double)length);
    if (length > g_height)
        length = g_height;
    draw_line(i, (g_height - length) / 2, length, img_start, (g_height * M_M_TIAL_SIZE) / p.distance, p);
}

double my_cos(float alpha)
{
    return (cos(alpha * (float)(M_PI / 180)));
}

void reset_door_info()
{
	g_door_info.col = 0;
	g_door_info.row = 0;
	g_door_info.dist = 0;
}

void save_door_info(int row, int col, double dist)
{
	if (g_door_info.dist > dist || g_door_info.dist == 0)
	{
		g_door_info.col = col;
		g_door_info.row = row;
		g_door_info.dist = dist;
	}
}

t_side is_door(int x, int y, double dist)
{
	int		row;
	int		col;
	t_str	**grid;

	col = y / M_M_TIAL_SIZE;
	row = x / M_M_TIAL_SIZE;
	grid = g_map->content;
	g_player.map_pos.y = g_player.pos.y / M_M_TIAL_SIZE;
	g_player.map_pos.x = g_player.pos.x / M_M_TIAL_SIZE;
	if (g_map->count <= col || col < 0 || grid[col]->count <= row || row < 0)
		return (0);
	if (ft_strchr("Dd", grid[col]->content[row]))
		save_door_info(row, col, dist);
	if (grid[col]->content[row] == 'D')
		return (close_door);
	if (grid[col]->content[row] == 'd')
		return (open_door);
	return (0);
}

void open_close_door()
{
	double dist;
	t_str	**grid;

	grid = g_map->content;
	if (g_keys.door == 1)
	{
		g_keys.door = 2;
		dist = distance((t_point){0,0}, (t_point){M_M_TIAL_SIZE, M_M_TIAL_SIZE});
		if (dist < g_door_info.dist || !g_door_info.dist)
			return;
		if (grid[g_door_info.col]->content[g_door_info.row] == 'D')
			grid[g_door_info.col]->content[g_door_info.row] = 'd';
		else if (grid[g_door_info.col]->content[g_door_info.row] == 'd')
			grid[g_door_info.col]->content[g_door_info.row] = 'D';
	}
}

void player_render()
{
	t_line	border;
	float view_start;
	int i;
	t_end_point p;
	t_side s;

	i = 0;
	move_player();
	open_close_door();
	init_mini_map_border(&border);
	draw_player_cercl(border, g_player.pos.x, g_player.pos.y, (int[]){0, 1, 2, 1, 0});
	view_start = g_player.angle + FOV / 2;
	reset_door_info();
	while (i < g_width)
	{
		if (view_start < 0)
			view_start += 360;
		if (view_start > 360)
			view_start -= 360;
		p = render_player_angle(view_start);
		s = is_door(p.point.x, p.point.y, p.distance);
		if (s)
			p.side = s;
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
