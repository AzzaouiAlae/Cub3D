/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:47:16 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:47:17 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

void	draw_ceil(t_draw_line data)
{
	int	i;
	int	color;

	i = 0;
	while (i < data.y)
	{
		color = darkness_effect_ceil(g_vars()->info.ceil_color, i);
		my_mlx_put_pixel(&g_vars()->win_img, data.x, i, color);
		i++;
	}
}

void	draw_floor(t_draw_line data, int i)
{
	int	color;

	data.y += i;
	while (data.y < g_vars()->height)
	{
		color = darkness_effect_floor(g_vars()->info.floor_color, data.y);
		my_mlx_put_pixel(&g_vars()->win_img, data.x, data.y, color);
		data.y++;
	}
}
