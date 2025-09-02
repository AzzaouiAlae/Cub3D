/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:03 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 23:04:44 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game_parse/game_parse.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

void	render_video(void)
{
	if (g_vars()->gate_video)
		gate_effect_video();
	else
		copy_resized_frame(&g_vars()->win_img, g_vars()->width, g_vars()->height
			- 70);
	mlx_put_image_to_window(g_vars()->mlx, g_vars()->win, g_vars()->win_img.img,
		0, 0);
}

int	render_game(void *pram)
{
	(void)pram;
	if (new_frame())
	{
		render_video();
	}
	else if (!should_play_video())
	{
		mouse_hook(NULL);
		move_player();
		map_game();
		if (!g_vars()->gate_video)
			cast_all_rays();
		mlx_put_image_to_window(g_vars()->mlx, g_vars()->win,
			g_vars()->win_img.img, 0, 0);
		mlx_put_image_to_window(g_vars()->mlx, g_vars()->win,
			g_vars()->map_img.img, MAP_MARGIN_X, MAP_MARGIN_Y);
	}
	if (should_clean_vlc())
	{
		clear_vlc();
	}
	return (0);
}
