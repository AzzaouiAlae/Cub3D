#include "cub3d.h"
#include "game_map/game_map.h"

void	hanle_parsing_error(t_game_map_status status)
{
	if (status == ok)
		return ;
	if (status == err_file_extension)
		ft_putstr_fd(2, "Error\nInvalid extension\n", 24);
	if (status == err_open_file)
		ft_putstr_fd(2, "Error\nOpen file\n", 16);
	if (status == err_invalid_info)
		ft_putstr_fd(2, "Error\nInvalid info\n", 19);
	if (status == err_invalid_map)
		ft_putstr_fd(2, "Error\nInvalid map\n", 18);
	ft_exit(255);
}

void	ft_init(void)
{
	g_mlx = mlx_init();
	mlx_get_screen_size(g_mlx, &g_width, &g_height);
	g_win = mlx_new_window(g_mlx, g_width, g_height, "Game");
	ft_bzero(&g_win_img, sizeof(t_data));
	g_win_img.img = mlx_new_image(g_mlx, g_width, g_height);
	g_win_img.addr = mlx_get_data_addr(g_win_img.img,
			&(g_win_img.bits_per_pixel), &(g_win_img.line_length),
			&(g_win_img.endian));
	ft_bzero(&g_info, sizeof(t_info));
	g_map = list_new(sizeof(t_str *));
	ft_bzero(&g_player, sizeof(t_player));
	ft_bzero(&g_keys, sizeof(t_keys));
	gettimeofday(&g_start_time, NULL);
}

void	render_mini_map_border(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < M_M_H)
	{
		j = 0;
		while (j < M_M_W)
		{
			if ((i >= 0 && i < M_M_BORDER_SIZE) || i >= M_M_H - M_M_BORDER_SIZE
				|| (j >= 0 && j < M_M_BORDER_SIZE) || j >= M_M_W
				- M_M_BORDER_SIZE)
				my_mlx_put_pixel(&g_win_img, M_M_MARGIN_X + j, M_M_MARGIN_Y + i,
					0xffffff);
			j++;
		}
		i++;
	}
}

void	render_player(t_line line, float x, float y, int x_ranges[])
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
			rend.x = x_start - line.start.x + M_M_MARGIN_X;
			rend.y = y - 2 + i - line.start.y + M_M_MARGIN_Y;
			my_mlx_put_pixel(&g_win_img, rend.x, rend.y, color);
			x_start++;
		}
		i++;
	}
}

void	render_pos(t_line line, float x, float y)
{
	int		row;
	int		col;
	int		color;
	t_str	**grid;
	t_point rend;

	col = y / M_M_TIAL_SIZE;
	row = x / M_M_TIAL_SIZE;
	grid = g_map->content;
	if (g_map->count <= col || col < 0 || grid[col]->count <= row || row < 0)
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

float tangent(float angle)
{
	float tan_val;

	if (angle == 0)
		angle = 0.0000001;
	if (!(angle > 0 && 180 > angle))
		angle = 360 - angle - 180;
	tan_val = tan(angle * (M_PI / 180));
	if (tan_val == 0)
		tan_val = 0.0000001;
	return tan_val;
}


float tangent2(float angle)
{
	float tan_val;

	if (angle == 0)
		angle = 0.0000001;
	if ((angle < 90 || 270 < angle))
		angle = 360 - angle - 180;
	tan_val = tan(angle * (M_PI / 180));
	if (tan_val == 0)
		tan_val = 0.0000001;
	return tan_val;
}

t_end_point ray_cast_y(t_point start, t_point *offset, float angle, float dist)
{
	t_end_point a;
    
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle > 0 && 180 > angle)
		a.point.y = floor(start.y / dist) * dist - 0.01;
	else
		a.point.y = floor(start.y / dist) * dist + dist;
	a.point.x = start.x + (start.y - a.point.y) / tangent(angle);
	if (angle > 0 && 180 > angle)
		offset->y = -dist;
	else
		offset->y = dist;
	offset->x = dist / tangent(angle);
    
    return a;
}

t_end_point ray_cast_x(t_point start, t_point *offset, float angle, float dist)
{
	t_end_point b;
    
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle < 90 || 270 < angle)
		b.point.x = floor(start.x / dist) * dist + dist;
	else
		b.point.x = floor(start.x / dist) * dist - 0.01;
	b.point.y = start.y + (start.x - b.point.x) * tangent2(angle);
	if (angle < 90 || 270 < angle)
		offset->x = dist;
	else
		offset->x = -dist;
	offset->y = dist * tangent2(angle);
    
    return b;
}

float distance(t_point p1, t_point p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrtf(dx * dx + dy * dy);
}

t_end_point ray_cast_dist(t_point start, t_point *offset, float angle, float dist)
{
	t_end_point p_x;
	t_end_point p_y;
	t_point offset_x;
	t_point offset_y;

	p_x = ray_cast_x(start, &offset_x, angle, M_M_TIAL_SIZE);
	p_y = ray_cast_y(start, &offset_y, angle, M_M_TIAL_SIZE);
	p_x.distance = distance(start, p_x.point);
	p_y.distance = distance(start, p_y.point);
	if (p_x.distance < p_y.distance)
	{
		p_x = ray_cast_x(start, &offset_x, angle, dist);
		p_x.distance = distance(start, p_x.point);
		offset->x = offset_x.x;
		offset->y = offset_x.y;
		return p_x;
	}
	else
	{
		p_y = ray_cast_y(start, &offset_y, angle, dist);
		p_y.distance = distance(start, p_y.point);
		offset->x = offset_y.x;
		offset->y = offset_y.y;
		return p_y;
	}
}

bool	is_posible_move(int x, int y)
{
	int		row;
	int		col;
	t_str	**grid;

	col = y / M_M_TIAL_SIZE;
	row = x / M_M_TIAL_SIZE;
	grid = g_map->content;
	if (g_map->count <= col || col < 0 || grid[col]->count <= row || row < 0)
		return (false);
	if (grid[col]->content[row] == '1')
		return (false);
	return (true);
}

void render_player_angle(t_line line, float angle)
{
	int i;
	t_point offset;
	t_end_point p;
	t_point rend;
	int		color;

	i = 0;
	p = ray_cast_dist(g_player.pos, &offset, angle, 1);
	color = 0xff5555;
	rend.x = p.point.x - line.start.x + M_M_MARGIN_X;
	rend.y = p.point.y - line.start.y + M_M_MARGIN_Y;
	while(is_posible_move(rend.x + line.start.x - M_M_MARGIN_X, rend.y + line.start.y - M_M_MARGIN_Y))
	{
		if (rend.x < M_M_MARGIN_X + M_M_W 
			&& rend.y < M_M_MARGIN_Y + M_M_H 
			&& rend.x >= M_M_MARGIN_X 
			&& rend.y >= M_M_MARGIN_Y)
		my_mlx_put_pixel(&g_win_img, round(rend.x), round(rend.y), color);
		rend.x += offset.x;
		rend.y += offset.y;
		i++;
	}
}

void	render_mini_map(void)
{
	t_line	line;
	float	x;
	float	y;
	float view_start;

	line.start.x = g_player.pos.x - ((float)(M_M_W - M_M_BORDER_SIZE * 2) / 2);
	line.start.y = g_player.pos.y - ((float)(M_M_H - M_M_BORDER_SIZE * 2) / 2);
	line.end.x = line.start.x + M_M_W - M_M_BORDER_SIZE * 2;
	line.end.y = line.start.y + M_M_H - M_M_BORDER_SIZE * 2;
	y = line.start.y;
	render_player(line, g_player.pos.x, g_player.pos.y, (int[]){0, 1, 2, 1, 0});
	while (y <= line.end.y)
	{
		x = line.start.x;
		while (x <= line.end.x)
		{
			render_pos(line, x, y);
			x++;
		}
		y++;
	}
	view_start = g_player.angle - FOV / 2;
	while (view_start < g_player.angle + FOV / 2) 
	{
		render_player_angle(line, view_start);
		view_start += (float)1 / ((float)M_M_W / (float)FOV);
	}
}

void	move_player(void)
{
	if (g_keys.w && is_posible_move(g_player.pos.x, g_player.pos.y
			- PLAYER_SPEED - 5))
		g_player.pos.y -= PLAYER_SPEED;
	if (g_keys.a && is_posible_move(g_player.pos.x - PLAYER_SPEED - 5,
			g_player.pos.y))
		g_player.pos.x -= PLAYER_SPEED;
	if (g_keys.d && is_posible_move(g_player.pos.x + PLAYER_SPEED + 2,
			g_player.pos.y))
		g_player.pos.x += PLAYER_SPEED;
	if (g_keys.s && is_posible_move(g_player.pos.x, g_player.pos.y
			+ PLAYER_SPEED + 2))
		g_player.pos.y += PLAYER_SPEED;
	if (g_keys.angle_min)
		g_player.angle -= ANGLE_SPEED;
	if (g_keys.angle_plus)
		g_player.angle += ANGLE_SPEED;
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

long get_time()
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec - g_start_time.tv_sec) * 1000000) 
		+ (curr_time.tv_usec - g_start_time.tv_usec);
}

void count_frame_per_sec()
{
	static struct timeval start_time;
	static int count; 
	struct timeval curr_time;
	long res;
	
	if (count == 0)
		gettimeofday(&start_time, NULL);
	count++;
	gettimeofday(&curr_time, NULL);
	res = ((curr_time.tv_sec - start_time.tv_sec) * 1000000) 
		+ (curr_time.tv_usec - start_time.tv_usec);
	if (res >= 1000000)
	{
		printf("%d\n", count);
		count = 0;
	}
}

void render_speed()
{
	static int render;
	long sleep;
	long time;

	time = get_time();
	sleep = 1000000 / FRAME_PER_SEC;
	sleep = (sleep * render) - time;
	if (sleep > 0 && sleep < 1000000 / FRAME_PER_SEC)
		usleep(sleep);
	if (render == FRAME_PER_SEC)
	{
		render = 0;
		gettimeofday(&g_start_time, NULL);
	}
	render++;
}

int	render_game(void *pram)
{
	(void)pram;
	clear_img((t_line){(t_point){M_M_MARGIN_X, M_M_MARGIN_Y},
		(t_point){M_M_MARGIN_X + M_M_W, M_M_MARGIN_Y + M_M_H}});
	move_player();
	render_mini_map();
	render_mini_map_border();
	mlx_put_image_to_window(g_mlx, g_win, g_win_img.img, 0, 0);
	render_speed();
	count_frame_per_sec();
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	ft_exit(0);
	return (0);
}

int	keydown_hook(int keycode, void *var)
{
	char	ch;

	ch = (char)keycode;
	(void)var;
	if (keycode == 65307)
		ft_exit(255);
	else if (!g_keys.w && ch == 'w')
		g_keys.w = 1;
	else if (!g_keys.a && ch == 'a')
		g_keys.a = 1;
	else if (!g_keys.d && ch == 'd')
		g_keys.d = 1;
	else if (!g_keys.s && ch == 's')
		g_keys.s = 1;
	else if (!g_keys.angle_min && ch == 83)
		g_keys.angle_min = 1;
	else if (!g_keys.angle_plus && ch == 81)
		g_keys.angle_plus = 1;
	return (0);
}

int	keyup_hook(int keycode, void *var)
{
	char	ch;

	ch = (char)keycode;
	(void)var;
	if (keycode == 65307)
		ft_exit(255);
	else if (ch == 'w')
		g_keys.w = 0;
	else if (ch == 'a')
		g_keys.a = 0;
	else if (ch == 'd')
		g_keys.d = 0;
	else if (ch == 's')
		g_keys.s = 0;
	else if (ch == 83)
		g_keys.angle_min = 0;
	else if (ch == 81)
		g_keys.angle_plus = 0;
	return (0);
}



int	main(int arg_c, char *arg_v[])
{
	if (arg_c != 2)
	{
		ft_putstr_fd(2, "Error\nInvalid args\n", 19);
		exit(255);
	}
	ft_init();
	hanle_parsing_error(game_map(arg_v[1], &g_info));
	mlx_hook(g_win, on_destroy, 0, close_window, NULL);
	mlx_hook(g_win, on_keyup, 1L<<1, keyup_hook, NULL);
	mlx_hook(g_win, on_keydown, 1L << 0, keydown_hook, NULL);
	mlx_loop_hook(g_mlx, render_game, NULL);
	mlx_loop(g_mlx);
	ft_free_all();
}
