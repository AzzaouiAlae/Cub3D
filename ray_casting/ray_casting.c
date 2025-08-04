#include "ray_casting.h"

t_end_point get_ray_x(float angle)
{
	t_end_point point;
	t_point offset;

	point = ray_cast_x(g_player.pos, &offset, angle, M_M_TIAL_SIZE);
	while(is_posible_move(point.point.x , point.point.y))
	{
		if (is_intersection(point.point, angle))
			break;
		point.point.x += offset.x;
		point.point.y += offset.y;
	}
	point.distance = distance(point.point, g_player.pos);
	return point;
}

t_end_point get_ray_y(float angle)
{
	t_end_point point;
	t_point offset;

	point = ray_cast_y(g_player.pos, &offset, angle, M_M_TIAL_SIZE);
	while(is_posible_move(point.point.x , point.point.y))
	{
		if (is_intersection(point.point, angle))
			break;
		point.point.x += offset.x;
		point.point.y += offset.y;
	}
	point.distance = distance(point.point, g_player.pos);
	return point;
}

t_end_point ray_cast(float angle)
{
	t_end_point point_x;
	t_end_point point_y;
	
	point_x = get_ray_x(angle);
	point_y = get_ray_y(angle);
	if (point_x.distance > point_y.distance)
		return point_y;
	else
		return point_x;
}
