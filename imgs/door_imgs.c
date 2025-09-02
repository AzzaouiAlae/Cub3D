/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:20:56 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:20:57 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgs.h"

int	fps(bool set, int fps)
{
	static int	value;

	if (set)
		value = fps;
	return (value);
}

t_data	*get_open_door_img(void)
{
	static int	i;
	static long	old_time;

	fps(true, O_FPS);
	return (get_wall_img(g_vars()->info.list_open_door,
			g_vars()->info.open_door, &i, &old_time));
}

t_data	*get_close_door_img(void)
{
	static int	i;
	static long	old_time;

	fps(true, C_FPS);
	return (get_wall_img(g_vars()->info.list_close_door,
			g_vars()->info.close_door, &i, &old_time));
}

t_data	*get_img(t_side side, t_side type)
{
	if (type == open_door)
		return (get_open_door_img());
	if (type == close_door)
		return (get_close_door_img());
	if (side == east)
		return (get_east_img());
	if (side == west)
		return (get_west_img());
	if (side == north)
		return (get_north_img());
	return (get_south_img());
}
