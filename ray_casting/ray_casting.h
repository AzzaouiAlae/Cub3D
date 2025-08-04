#ifndef RAY_CASTING_H
#define RAY_CASTING_H
#include "../cub3d.h"
#include "../game_map/game_map.h"

t_end_point ray_cast_y(t_point start, t_point *offset, float angle, float dist);
t_end_point ray_cast_x(t_point start, t_point *offset, float angle, float dist);
t_end_point ray_cast_dist(t_point start, t_point *offset, float angle, float dist);
t_end_point get_ray_x(float angle);
t_end_point get_ray_y(float angle);
t_end_point ray_cast(float angle);

#endif