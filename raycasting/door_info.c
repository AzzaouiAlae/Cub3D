/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:21:12 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:21:13 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

t_door	*door_info(void)
{
	static t_door	door_info;

	return (&door_info);
}

void	save_door_info(int x, int y, double dist)
{
	if (dist < door_info()->dist || !door_info()->dist)
	{
		door_info()->col = x / TILESIZE;
		door_info()->row = y / TILESIZE;
		door_info()->dist = dist;
	}
}

void	reset_door_info(void)
{
	door_info()->col = 0;
	door_info()->row = 0;
	door_info()->dist = 0;
}

void	check_door(t_point p, double dist)
{
	t_pos_type	res;

	res = check_pos(p.x, p.y);
	if (res == e_opened_gate || res == e_closed_gate)
		save_door_info(p.x, p.y, dist);
}

t_side	get_side(t_point p, t_point start, char inter, t_side *type)
{
	t_pos_type	res;

	*type = north;
	res = check_pos(p.x, p.y);
	if (res == e_opened_gate)
		*type = open_door;
	else if (res == e_closed_gate)
		*type = close_door;
	if (inter == 'x')
	{
		if (p.x > start.x)
			return (east);
		else
			return (west);
	}
	else if (inter == 'y')
	{
		if (p.y < start.y)
			return (south);
		else
			return (north);
	}
	return (north);
}
