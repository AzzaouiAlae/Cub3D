#ifndef PLAYER_H
#define PLAYER_H
#include "../cub3d.h"
#include <stdbool.h>
#include <unistd.h>

void draw_circle(t_data *img, t_point p, int r, int color);
void move_player();
bool is_valid_move(double x, double y);
bool is_open_gate(int x, int y);
bool is_teleportation_move(t_point dir);
void calculate_player_speed();

#endif
