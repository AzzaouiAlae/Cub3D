#ifndef PLAYER_H
#define PLAYER_H
#include "../cub3d.h"
#include <stdbool.h>

void draw_circle(t_data *img, t_point p, int r, int color);
void move_player();
bool is_valid_move(int x, int y);

#endif