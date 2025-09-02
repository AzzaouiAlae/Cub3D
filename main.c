#include "cub3d.h"
#include "game_map/game_map.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

bool			g_gate_video;
const void			*g_mlx;
const void			*g_win;
t_list			*g_map;
t_info			g_info;
t_data			g_win_img;
double			g_width;
double			g_height;
t_player		g_player;
t_keys			g_keys;
t_data			g_map_img;
size_t			g_time;
size_t			g_old_time;

size_t get_curr_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)(time.tv_sec * 1000000 + time.tv_usec));
}

void	normalize_angle(double *angle)
{
	if (*angle < 0.0)
		*angle += 360.0;
	else if (*angle > 360.0)
		*angle -= 360.0;
}

void	my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_get_pixel(t_data *data, int x, int y)
{
	char	*dst;

	if (!data || !data->addr)
		return (0);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*((unsigned int *)dst));
}

t_data	*create_image(char *relative_path)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->img = mlx_xpm_file_to_image(g_mlx, relative_path, &(data->img_width),
			&(data->img_height));
	if (!(data->img))
		return (NULL);
	save_img(data->img);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	return (data);
}

void init_gate_video(t_line *vdo_brd, t_point *step)
{
	step->x = ((g_width / 2) / 10);
	step->y = ((g_height / 2) / 10);
	vdo_brd->start.x = (g_width / 2) - step->x;
	vdo_brd->start.y = (g_height / 2) - step->x;
	vdo_brd->end.x = (g_width / 2) + step->x;
	vdo_brd->end.y = (g_height / 2) + step->x;
}

void gate_effect_video()
{
	static int		first_time = 1;
	static t_line	vdo_brd;
	static t_point	step;

	if (first_time)
		init_gate_video(&vdo_brd, &step);
	if (vdo_brd.start.x > 0 && vdo_brd.start.y > 0
		&& vdo_brd.end.x < g_width && g_height > vdo_brd.end.y)
	{
		first_time = 0;
		set_frame_start_end(vdo_brd.start.x, vdo_brd.start.y, vdo_brd.end.x, vdo_brd.end.y);
		copy_start_end_frame(&g_win_img);
		vdo_brd.start.x -= step.x;
		vdo_brd.start.y -= step.y;
		vdo_brd.end.x += step.x;
		vdo_brd.end.y += step.y;
	}
	else
	{
		first_time = 1;
		g_gate_video = false;
	}
}

int	render_game(void *pram)
{
	(void)pram;
	if (new_frame())
    {
		if (g_gate_video)
			gate_effect_video();
		else
        	copy_resized_frame(&g_win_img, g_width, g_height - 70);
        mlx_put_image_to_window(g_mlx, g_win, g_win_img.img, 0, 0);
    }
	else if (!should_play_video())
	{
		mouse_hook(NULL);
		move_player();
		map_game();
		if (!g_gate_video)
			cast_all_rays();
		mlx_put_image_to_window(g_mlx, g_win, g_win_img.img, 0, 0);
		mlx_put_image_to_window(g_mlx, g_win, g_map_img.img, MAP_MARGIN_X,
			MAP_MARGIN_Y);
	}
	if (should_clean_vlc())
	{
		clear_vlc();
	}
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
	(void)ch;
	if (keycode == 65307)
		ft_exit(0);
	if (ch == 'w')
		g_keys.w = 1;
	if (ch == 'd')
		g_keys.d = 1;
	if (ch == 'a')
		g_keys.a = 1;
	if (ch == 's')
		g_keys.s = 1;
	if (!g_keys.o && ch == 'o')
		g_keys.o = 1;
	if (ch == 83)
		g_keys.right = 1;
	if (ch == 81)
		g_keys.left = 1;
	return (0);
}

int	keyup_hook(int keycode, void *var)
{
	char	ch;

	(void)var;
	ch = (char)keycode;
	if (ch == 'w')
		g_keys.w = 0;
	if (ch == 'd')
		g_keys.d = 0;
	if (ch == 'a')
		g_keys.a = 0;
	if (ch == 's')
		g_keys.s = 0;
	if (g_keys.o == 2 && ch == 'o')
		g_keys.o = 0;
	if (ch == 'u')
	{
		g_keys.mouse = !g_keys.mouse;
	}
	if (ch == 83)
		g_keys.right = 0;
	if (ch == 81)
		g_keys.left = 0;
	return (0);
}

// if (g_keys.mouse)
// 	mlx_mouse_hide(g_mlx, g_win);
// else
// 	mlx_mouse_show(g_mlx, g_win);

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
	int	w;
	int	h;

	g_mlx = mlx_init();
	mlx_get_screen_size(g_mlx, &w, &h);
	g_width = w;
	g_height = h;
	g_win = mlx_new_window(g_mlx, g_width, g_height, "Game");
	g_win_img.img = mlx_new_image(g_mlx, g_width, g_height);
	g_win_img.addr = mlx_get_data_addr(g_win_img.img,
			&(g_win_img.bits_per_pixel), &(g_win_img.line_length),
			&(g_win_img.endian));
	g_map_img.img = mlx_new_image(g_mlx, MAP_W, MAP_HEIGHT);
	g_map_img.addr = mlx_get_data_addr(g_map_img.img,
			&(g_map_img.bits_per_pixel), &(g_map_img.line_length),
			&(g_map_img.endian));
	g_map = list_new(sizeof(t_str *));
	g_time = get_curr_time();
	init_flags();
}

int mouse_hook(void *param)
{
	(void)param;
	int x = 10;
	int y = 10;

	if (g_keys.mouse)
	{
		mlx_mouse_get_pos(g_mlx, g_win, &x, &y);
		x = g_width / 2 - x;
		g_player.angle += x * DPI;
		mlx_mouse_move(g_mlx, g_win, g_width / 2, g_height / 2);
		mlx_mouse_get_pos(g_mlx, g_win, &x, &y);
	}
	return (0);
}

int	main(int arg_c, char **arg_v)
{
	if (arg_c != 2)
	{
		ft_putstr_fd(2, "Error\nInvalid args\n", 19);
		exit(255);
	}
	ft_init();
	hanle_parsing_error(game_map(arg_v[1], &g_info));
	mlx_hook(g_win, on_destroy, 0, close_window, NULL);
	mlx_hook(g_win, on_keydown, 1L << 0, keydown_hook, NULL);
	mlx_hook(g_win, on_keyup, 1L << 1, keyup_hook, NULL);
	mlx_loop_hook(g_mlx, render_game, NULL);
	sound_track((char *[]){"media/void.mp3", 0});
	// play_video("media/blasphemous_intro.mp4");
	mlx_loop(g_mlx);
	ft_free_all();

	return (0);
}
