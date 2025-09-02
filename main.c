/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:12:23 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 18:48:51 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game_parse/game_parse.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

bool			g_gate_video;
void			*g_mlx;
void			*g_win;
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

void	init_gate_video(t_line *vdo_brd, t_point *step)
{
	step->x = ((g_width / 2) / 10);
	step->y = ((g_height / 2) / 10);
	vdo_brd->start.x = (g_width / 2) - step->x;
	vdo_brd->start.y = (g_height / 2) - step->x;
	vdo_brd->end.x = (g_width / 2) + step->x;
	vdo_brd->end.y = (g_height / 2) + step->x;
}

void	gate_effect_video(void)
{
	static int		first_time = 1;
	static t_line	vdo_brd;
	static t_point	step;

	if (first_time)
		init_gate_video(&vdo_brd, &step);
	if (vdo_brd.start.x > 0 && vdo_brd.start.y > 0 && vdo_brd.end.x < g_width
		&& g_height > vdo_brd.end.y)
	{
		first_time = 0;
		set_frame_start_end(vdo_brd.start.x, vdo_brd.start.y, vdo_brd.end.x,
			vdo_brd.end.y);
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

int	main(int arg_c, char **arg_v)
{
	if (arg_c != 2)
	{
		ft_putstr_fd(2, "Error\nInvalid args\n", 19);
		exit(255);
	}
	ft_init();
	hanle_parsing_error(game_parse(arg_v[1], &g_info));
	mlx_hook(g_win, on_destroy, 0, close_window, NULL);
	mlx_hook(g_win, on_keydown, 1L << 0, keydown_hook, NULL);
	mlx_hook(g_win, on_keyup, 1L << 1, keyup_hook, NULL);
	mlx_loop_hook(g_mlx, render_game, NULL);
	sound_track((char *[]){"media/void2.mp", 0});
	// play_video("media/blasphemous_intro.mp4");
	mlx_loop(g_mlx);
	ft_free_all();
	return (0);
}
