/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:12:23 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 23:11:54 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game_parse/game_parse.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

void	init_gate_video(t_line *vdo_brd, t_point *step)
{
	step->x = ((g_vars()->width / 2) / 10);
	step->y = ((g_vars()->height / 2) / 10);
	vdo_brd->start.x = (g_vars()->width / 2) - step->x;
	vdo_brd->start.y = (g_vars()->height / 2) - step->x;
	vdo_brd->end.x = (g_vars()->width / 2) + step->x;
	vdo_brd->end.y = (g_vars()->height / 2) + step->x;
}

void	gate_effect_video(void)
{
	static int		first_time = 1;
	static t_line	vdo_brd;
	static t_point	step;

	if (first_time)
		init_gate_video(&vdo_brd, &step);
	if (vdo_brd.start.x > 0 && vdo_brd.start.y > 0
		&& vdo_brd.end.x < g_vars()->width && g_vars()->height > vdo_brd.end.y)
	{
		first_time = 0;
		set_frame_start_end(vdo_brd.start.x, vdo_brd.start.y, vdo_brd.end.x,
			vdo_brd.end.y);
		copy_start_end_frame(&g_vars()->win_img);
		vdo_brd.start.x -= step.x;
		vdo_brd.start.y -= step.y;
		vdo_brd.end.x += step.x;
		vdo_brd.end.y += step.y;
	}
	else
	{
		first_time = 1;
		g_vars()->gate_video = false;
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
	int				w;
	int				h;
	t_global_vars	*vars;

	vars = g_vars();
	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &w, &h);
	vars->width = w;
	vars->height = h;
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "Game");
	vars->win_img.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->win_img.addr = mlx_get_data_addr(vars->win_img.img,
			&vars->win_img.bits_per_pixel, &vars->win_img.line_length,
			&vars->win_img.endian);
	vars->map_img.img = mlx_new_image(vars->mlx, MAP_W, MAP_HEIGHT);
	vars->map_img.addr = mlx_get_data_addr(vars->map_img.img,
			&vars->map_img.bits_per_pixel, &vars->map_img.line_length,
			&vars->map_img.endian);
	vars->map = list_new(sizeof(t_str *));
	vars->time = get_curr_time();
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
	hanle_parsing_error(game_parse(arg_v[1], &g_vars()->info));
	mlx_hook(g_vars()->win, on_destroy, 0, close_window, NULL);
	mlx_hook(g_vars()->win, on_keydown, 1L << 0, keydown_hook, NULL);
	mlx_hook(g_vars()->win, on_keyup, 1L << 1, keyup_hook, NULL);
	mlx_loop_hook(g_vars()->mlx, render_game, NULL);
	sound_track((char *[]){"media/void2.mp3", 0});
	play_video("media/blasphemous_intro.mp4");
	mlx_loop(g_vars()->mlx);
	ft_free_all();
	return (0);
}
