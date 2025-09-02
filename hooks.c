/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:20:13 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 16:47:09 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game_parse/game_parse.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

int	mouse_hook(void *param)
{
	int	x;
	int	y;

	(void)param;
	x = 10;
	y = 10;
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

int	close_window(void *param)
{
	(void)param;
	ft_exit(0);
	return (0);
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
