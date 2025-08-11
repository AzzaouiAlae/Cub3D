#ifndef PLAYER_H
#define PLAYER_H
#include "../cub3d.h"

void player_render();
t_end_point render_player_angle(float angle);
void	move_player(void);
void	draw_player_cercl(t_line border, float x, float y, int x_ranges[]);
void render_line_angle(float angle, float dist, int	color);

#endif