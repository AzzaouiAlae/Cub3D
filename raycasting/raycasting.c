#include "raycasting.h"
#include "../map_game/map_game.h"

t_door g_door_info;

bool is_valid_ray(int x, int y)
{
	return check_pos(x, y) == e_empty;
}

bool in_range(double start, double end, double num)
{
	return (start <= num && end >= num);
}

double	my_tan(double angle, char inter)
{
	if (inter == 'y')
	{
		if (!(angle > 0 && 180 > angle))
		angle = 360 - angle - 180;
	}
	else if (inter == 'x')
	{
		if ((angle <= 90 || 270 < angle))
			angle = 360 - angle - 180;
	}
	normalize_angle(&angle);
	if (angle == 0)
		angle = 0.0001;
	return (tan(angle * (M_PI / 180)));
}

double my_cos(float alpha)
{
    return (cos(alpha * (float)(M_PI / 180)));
}

t_end_point x_intersections(t_point start, double angle)
{
	t_end_point p;

	if (!(in_range(0, 90, angle) || in_range(270, 360, angle)))
	{
		p.end.x = floor(start.x / TILESIZE) * TILESIZE - 0.0001;
		p.delta_dist.x = -TILESIZE;
	}
	else
	{
		p.end.x = floor(start.x / TILESIZE) * TILESIZE + TILESIZE;
		p.delta_dist.x = TILESIZE;
	}
	p.end.y = start.y + fabs(start.x - p.end.x) * my_tan(angle, 'x');
	p.delta_dist.y = TILESIZE * my_tan(angle, 'x');
	while (is_valid_ray(p.end.x, p.end.y))
	{
		p.end.x += p.delta_dist.x;
		p.end.y += p.delta_dist.y;
	}
	if (p.end.x > start.x)
		p.side = east;
	else
		p.side = west;
	p.distance = ph_distance(start, p.end);
	return (p);
}

t_end_point y_intersections(t_point start, double angle)
{
	t_end_point p;

	if (in_range(0, 180, angle))
	{
		p.end.y = floor(start.y / TILESIZE) * TILESIZE - 0.0001;
		p.delta_dist.y = -TILESIZE;
	}
	else
	{
		p.end.y = floor(start.y / TILESIZE) * TILESIZE + TILESIZE;
		p.delta_dist.y = TILESIZE;
	}
	p.end.x = start.x + fabs(start.y - p.end.y) / my_tan(angle, 'y');
	p.delta_dist.x = TILESIZE / my_tan(angle, 'y');
	while (is_valid_ray(p.end.x, p.end.y))
	{
		p.end.x += p.delta_dist.x;
		p.end.y += p.delta_dist.y;
	}
	if (p.end.y < start.y)
		p.side = south;
	else
		p.side = north;
	p.distance = ph_distance(start, p.end);
	return (p);
}

t_end_point raycaster(t_point start, double angle)
{
	t_end_point point_x;
	t_end_point point_y;

	point_x = x_intersections(start, angle);
	point_y = y_intersections(start, angle);
	if (point_x.distance < point_y.distance)
		return (point_x);
	return (point_y);
}

t_data *get_img(t_side side)
{
	if (side == east)
		return g_info.east;
	if (side == west)
		return g_info.west;
	if (side == north)
		return g_info.north;
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
	img = get_img(p.side);
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

	img = get_img(p.side);
    int length = (g_height * TILESIZE) / p.distance;
	double tile_x = p.end.y - floor(p.end.y / TILESIZE) * TILESIZE; 
	if (p.side == north || p.side == south)
		tile_x = p.end.x - floor(p.end.x / TILESIZE) * TILESIZE; 
	img_start.x = (img->img_width / TILESIZE) * tile_x;
	img_start.y = (g_height - length) / 2;
	if (img_start.y > 0)
		img_start.y = 0;
	else 
		img_start.y = fabs(img_start.y) * ((double)img->img_height / (double)length);
    if (length > g_height)
        length = g_height;
    draw_line(i, (g_height - length) / 2, length, img_start, (g_height * TILESIZE) / p.distance, p);
}

void	cast_all_rays()
{
	double	dpr;
	double angle;
	double real_alpha;
	t_end_point p;
	int i;
	t_line		map_pos;
	t_point		start;

	i = 0;
	dpr = FOV / g_width;
	angle =  g_player.angle + (FOV / 2);
	real_alpha = 30;
	init_map_pos(&map_pos, &start);
	while (i < g_width)
	{
		normalize_angle(&angle);
		p = raycaster(g_player.pixl_pos, angle);
		// draw_circle(&g_map_img, (t_point){p.end.x - start.x,
		// p.end.y - start.y}, 2, 0xff5555);
		p.distance *= my_cos(real_alpha);
		render_walls(p, i);
		angle -= dpr;
		real_alpha -= dpr;
		i++;
	}
}
