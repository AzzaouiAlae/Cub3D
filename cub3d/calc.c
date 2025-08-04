#include "cub3d.h"

float distance(t_point p1, t_point p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrtf(dx * dx + dy * dy);
}

float tangent(float angle)
{
	float tan_val;

	if (angle == 0)
		angle = 0.0000001;
	if (!(angle > 0 && 180 > angle))
		angle = 360 - angle - 180;
	tan_val = tan(angle * (M_PI / 180));
	if (tan_val == 0)
		tan_val = 0.0000001;
	return tan_val;
}

float tangent2(float angle)
{
	float tan_val;

	if (angle == 0)
		angle = 0.0000001;
	if ((angle <= 90 || 270 < angle))
		angle = 360 - angle - 180;
	tan_val = tan(angle * (M_PI / 180));
	if (tan_val == 0)
		tan_val = 0.0000001;
	return tan_val;
}

t_point calc_align(t_point p1, t_point p2, int d)
{
	t_point point;

    double t = d / distance(p1, p2);
    point.x = (1 - t) * p1.x + t * p2.x;
    point.y = (1 - t) * p1.y + t * p2.y;
    return (point);
}

bool in_range(float start, float end, float num)
{
	return (num >= start && num <= end);
}