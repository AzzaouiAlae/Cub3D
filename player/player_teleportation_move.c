/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_teleportation_move.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:55:34 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:55:35 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_game/map_game.h"
#include "player.h"

bool	is_teleportation_move(t_point dir)
{
	t_point	pos;

	pos.x = dir.x * (TILESIZE + SAFETY * 3);
	pos.y = dir.y * (TILESIZE + SAFETY * 3);
	if (is_valid_move(pos.x, pos.y))
	{
		play_video("media/gate5.mp4");
		g_vars()->gate_video = true;
		g_vars()->player.pixl_pos.x += pos.x;
		g_vars()->player.pixl_pos.y += pos.y;
		return (true);
	}
	return (false);
}

bool	is_open_gate(int x, int y)
{
	return (check_pos(g_vars()->player.pixl_pos.x + x,
			g_vars()->player.pixl_pos.y + y) == e_opened_gate);
}
