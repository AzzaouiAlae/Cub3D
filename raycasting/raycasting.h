#ifndef RAYCASTING_H
#define RAYCASTING_H
#include "../cub3d.h"

t_end_point raycaster(t_point start, double angle);
void	cast_all_rays();
void draw_player_dir(double angle, double dir_dist, t_point	start)
;

#endif
