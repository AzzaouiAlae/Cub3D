#include "ray_casting.h"

t_end_point ray_cast_y(t_point start, t_point *offset, float angle, float dist)
{
	t_end_point a;
    
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	if (angle > 0 && 180 > angle)
		a.point.y = floor(start.y / dist) * dist - 0.000001;
	else
		a.point.y = floor(start.y / dist) * dist + dist;
	a.point.x = start.x + fabs(start.y - a.point.y) / tangent(angle);
	if (angle > 0 && 180 > angle)
		offset->y = -dist;
	else
		offset->y = dist;
	offset->x = dist / tangent(angle);
	a.distance = distance((t_point){0,0}, *offset);
	if (a.point.y < start.y)
		a.side = north;
	else
		a.side = south;
    return a;
}

t_end_point ray_cast_x(t_point start, t_point *offset, float angle, float dist)
{
	t_end_point b;
    
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	if (angle < 90 || 270 < angle)
		b.point.x = floor(start.x / dist) * dist + dist;
	else
		b.point.x = floor(start.x / dist) * dist - 0.000001;
	offset->y = dist * tangent2(angle);
	b.point.y = start.y + fabs(start.x - b.point.x) * tangent2(angle); 
	if (angle < 90 || 270 < angle)
		offset->x = dist;
	else
		offset->x = -dist;
    b.distance = distance((t_point){0,0}, *offset);
	if (b.point.x > start.x)
		b.side = east;
	else
		b.side = west;
    return b;
}

t_end_point ray_cast_dist(t_point start, t_point *offset, float angle, float dist)
{
	t_end_point p_x;
	t_end_point p_y;
	t_point offset_x;
	t_point offset_y;

	p_x = ray_cast_x(start, &offset_x, angle, M_M_TIAL_SIZE);
	p_y = ray_cast_y(start, &offset_y, angle, M_M_TIAL_SIZE);
	if (p_x.distance < p_y.distance)
	{
		p_x = ray_cast_x(start, &offset_x, angle, dist);
		p_x.distance = distance(start, p_x.point);
		offset->x = offset_x.x;
		offset->y = offset_x.y;
		return p_x;
	}
	else
	{
		p_y = ray_cast_y(start, &offset_y, angle, dist);
		p_y.distance = distance(start, p_y.point);
		offset->x = offset_y.x;
		offset->y = offset_y.y;
		return p_y;
	}
}
