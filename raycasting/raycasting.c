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
		angle = 180 - angle;
	}
	else if (inter == 'x')
	{
		if ((angle <= 90 || 270 < angle))
			angle = 180 - angle;
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

void save_door_info(int x, int y, double dist)
{
	if (dist < g_door_info.dist || !g_door_info.dist)
	{
		g_door_info.col = x / TILESIZE;
		g_door_info.row = y / TILESIZE;
		g_door_info.dist = dist;
	}
}

void reset_door_info()
{
	g_door_info.col = 0;
	g_door_info.row = 0;
	g_door_info.dist = 0;
}

void check_door(t_point p, double dist)
{
	t_pos_type res;

	res = check_pos(p.x, p.y);
	if (res == e_opened_gate || res == e_closed_gate)
		save_door_info(p.x, p.y, dist);
}

t_side get_side(t_point p, t_point start,char inter)
{
	t_pos_type res;

	res = check_pos(p.x, p.y);
	if (res == e_opened_gate)
		return open_door;
	else if (res == e_closed_gate)
		return close_door;
	if (inter == 'x')
	{
		if (p.x > start.x)
			return east;
		else
			return west;
	}
	else if (inter == 'y')
	{
		if (p.y < start.y)
			return south;
		else
			return north;
	}
	return north;
}

t_end_point x_intersections(t_point start, double angle)
{
	t_end_point p;

	if (!(in_range(0, 90, angle) || in_range(270, 360, angle)))
	{
		p.end.x = floor(start.x / TILESIZE) * TILESIZE - 0.000000001;
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
	p.distance = ph_distance(start, p.end);
	p.side = get_side(p.end, start, 'x');
	return (p);
}

t_end_point y_intersections(t_point start, double angle)
{
	t_end_point p;

	if (in_range(0, 180, angle))
	{
		p.end.y = floor(start.y / TILESIZE) * TILESIZE - 0.000000001;
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
	p.distance = ph_distance(start, p.end);
	p.side = get_side(p.end, start, 'y');
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

int darkness_effect(int color, double dist)
{
	t_color c;
	int res;

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
int darkness_effect_ceil(int color, double dist)
{
	t_color c;
	int res;

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

int darkness_effect_floor(int color, double dist)
{
	t_color c;
	int res;

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
		color = darkness_effect_ceil(g_info.ceil_color, i);
		my_mlx_put_pixel(&g_win_img, x, i, color);
		i++;
	}
	i = 0;
	while(i < l && y + i < g_height)
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

void render_walls(t_end_point p, int i)
{
    t_point img_start;
	t_data *img;

	img = get_img(p.side);
    int length = (g_height * (double)TILESIZE) / p.distance;
	double tile_x = p.end.y - floor(p.end.y / (double)TILESIZE) * (double)TILESIZE;
	if (p.side == north || p.side == south)
		tile_x = p.end.x - floor(p.end.x / (double)TILESIZE) * (double)TILESIZE;
	img_start.x = (img->img_width / (double)TILESIZE) * tile_x;
	img_start.y = (g_height - length) / 2;
	if (img_start.y > 0)
		img_start.y = 0;
	else
		img_start.y = fabs(img_start.y) * ((double)img->img_height / (double)length);
    if (length > g_height)
        length = g_height;
    draw_line(i, (g_height - length) / 2, length, img_start, (g_height * (double)TILESIZE) / p.distance, p);
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
	reset_door_info();
	while (i < g_width)
	{
		normalize_angle(&angle);
		p = raycaster(g_player.pixl_pos, angle);
		check_door(p.end, p.distance);
		p.distance *= my_cos(real_alpha);
		render_walls(p, i);
		angle -= dpr;
		real_alpha -= dpr;
		i++;
	}
}
