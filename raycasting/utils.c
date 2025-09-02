/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:56:22 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 18:01:31 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../imgs/imgs.h"
#include "../map_game/map_game.h"
#include "raycasting.h"

bool	is_valid_ray(int x, int y)
{
	return (check_pos(x, y) == e_empty);
}

bool	in_range(double start, double end, double num)
{
	return (start <= num && end >= num);
}

double	my_tan(double angle, char inter)
{
	if (inter == 'y')
	{
		if (!(angle > 0 && 180 > angle))
			angle = 180 - angle;
	}
	else if (inter == 'x')
	{
		if ((angle <= 90 || 270 < angle))
			angle = 180 - angle;
	}
	normalize_angle(&angle);
	if (angle == 0)
		angle = 0.0001;
	return (tan(angle * (M_PI / 180)));
}

double	my_cos(float alpha)
{
	return (cos(alpha * (float)(M_PI / 180)));
}
