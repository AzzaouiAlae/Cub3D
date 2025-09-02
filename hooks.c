/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:20:13 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 23:04:52 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game_parse/game_parse.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

t_global_vars	*g_vars(void)
{
	static t_global_vars	vars;

	return (&vars);
}

int	mouse_hook(void *param)
{
	int	x;
	int	y;

	(void)param;
	x = 10;
	y = 10;
	if (g_vars()->keys.mouse)
	{
		mlx_mouse_get_pos(g_vars()->mlx, g_vars()->win, &x, &y);
		x = g_vars()->width / 2 - x;
		g_vars()->player.angle += x * DPI;
		mlx_mouse_move(g_vars()->mlx, g_vars()->win, g_vars()->width / 2,
			g_vars()->height / 2);
		mlx_mouse_get_pos(g_vars()->mlx, g_vars()->win, &x, &y);
	}
	return (0);
}

int	keyup_hook(int keycode, void *var)
{
	char	ch;

	(void)var;
	ch = (char)keycode;
	if (ch == 'w')
		g_vars()->keys.w = 0;
	if (ch == 'd')
		g_vars()->keys.d = 0;
	if (ch == 'a')
		g_vars()->keys.a = 0;
	if (ch == 's')
		g_vars()->keys.s = 0;
	if (g_vars()->keys.o == 2 && ch == 'o')
		g_vars()->keys.o = 0;
	if (ch == 'u')
	{
		g_vars()->keys.mouse = !g_vars()->keys.mouse;
	}
	if (ch == 83)
		g_vars()->keys.right = 0;
	if (ch == 81)
		g_vars()->keys.left = 0;
	return (0);
}

// if (g_vars()->keys.mouse)
// 	mlx_mouse_hide(g_vars()->mlx, g_vars()->win);
// else
// 	mlx_mouse_show(g_vars()->mlx, g_vars()->win);

int	keydown_hook(int keycode, void *var)
{
	char	ch;

	ch = (char)keycode;
	(void)var;
	(void)ch;
	if (keycode == 65307)
		ft_exit(0);
	if (ch == 'w')
		g_vars()->keys.w = 1;
	if (ch == 'd')
		g_vars()->keys.d = 1;
	if (ch == 'a')
		g_vars()->keys.a = 1;
	if (ch == 's')
		g_vars()->keys.s = 1;
	if (!g_vars()->keys.o && ch == 'o')
		g_vars()->keys.o = 1;
	if (ch == 83)
		g_vars()->keys.right = 1;
	if (ch == 81)
		g_vars()->keys.left = 1;
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	ft_exit(0);
	return (0);
}
