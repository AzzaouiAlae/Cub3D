#ifndef MAP_GAME_H
#define MAP_GAME_H
#include "../cub3d.h"


typedef enum e_pos_type
{
	e_invalid,
	e_space,
	e_empty,
	e_wall,
	e_opened_gate,
	e_closed_gate
}	t_pos_type;

void map_game();
t_pos_type	check_pos(double x, double y);
void	init_map_pos(t_line *map_pos, t_point *start);
#endif
