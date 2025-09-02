/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:55:44 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:57:26 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_game/map_game.h"
#include "../raycasting/raycasting.h"
#include "player.h"

bool	is_valid_move(double x, double y)
{
	t_point	pos;

	pos.x = g_vars()->player.pixl_pos.x + x;
	pos.y = g_vars()->player.pixl_pos.y + y;
	if (check_pos(pos.x, pos.y) != e_empty)
		return (false);
	if (check_pos(pos.x + SAFETY, pos.y) != e_empty)
		return (false);
	if (check_pos(pos.x, pos.y + SAFETY) != e_empty)
		return (false);
	if (check_pos(pos.x - SAFETY, pos.y) != e_empty)
		return (false);
	if (check_pos(pos.x, pos.y - SAFETY) != e_empty)
		return (false);
	return (true);
}

void	player_walk(double angle, double speed)
{
	t_point	dir;
	int		i;

	i = 0;
	normalize_angle(&angle);
	dir.x = cos(angle * M_PI / 180);
	dir.y = -sin(angle * M_PI / 180);
	while (i < speed)
	{
		if (is_open_gate(dir.x * SAFETY * 2, dir.y * SAFETY * 2))
		{
			if (is_teleportation_move(dir))
				break ;
		}
		if (is_valid_move(dir.x, 0))
			g_vars()->player.pixl_pos.x += dir.x;
		if (is_valid_move(0, dir.y))
			g_vars()->player.pixl_pos.y += dir.y;
		i++;
	}
}

void	open_close_door(void)
{
	t_str	**the_map;
	double	dist;

	g_vars()->keys.o = 2;
	the_map = g_vars()->map->content;
	dist = ph_distance((t_point){0, 0}, (t_point){TILESIZE * 1.5, TILESIZE
			* 1.5});
	if (dist < door_info()->dist)
		return ;
	if (the_map[door_info()->row]->content[door_info()->col] == 'D')
		the_map[door_info()->row]->content[door_info()->col] = 'd';
	else if (the_map[door_info()->row]->content[door_info()->col] == 'd')
		the_map[door_info()->row]->content[door_info()->col] = 'D';
}

void	media_walking(void)
{
	static int	audio_index;

	if (!(g_vars()->keys.w || g_vars()->keys.d || g_vars()->keys.a
			|| g_vars()->keys.s))
		return ;
	if (audio_index > 2)
		audio_index = 0;
	set_play_speed(100);
	if (audio_index == 0)
		play_audio("media/walking1.mp3");
	else if (audio_index == 1)
		play_audio("media/walking2.mp3");
	else if (audio_index == 2)
		play_audio("media/walking3.mp3");
	audio_index++;
}

void	move_player(void)
{
	g_vars()->old_time = g_vars()->time;
	g_vars()->time = get_curr_time();
	calculate_player_speed();
	media_walking();
	if (g_vars()->keys.w)
		player_walk(g_vars()->player.angle, g_vars()->player.move_speed);
	if (g_vars()->keys.d)
		player_walk(g_vars()->player.angle - 90, g_vars()->player.move_speed);
	if (g_vars()->keys.a)
		player_walk(g_vars()->player.angle + 90, g_vars()->player.move_speed);
	if (g_vars()->keys.s)
		player_walk(g_vars()->player.angle + 180, g_vars()->player.move_speed);
	if (g_vars()->keys.left)
	{
		g_vars()->player.angle += g_vars()->player.turn_speed;
		normalize_angle(&g_vars()->player.angle);
	}
	if (g_vars()->keys.right)
	{
		g_vars()->player.angle -= g_vars()->player.turn_speed;
		normalize_angle(&g_vars()->player.angle);
	}
	if (g_vars()->keys.o == 1)
		open_close_door();
}
