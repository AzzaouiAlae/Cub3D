#ifndef MAP_GAME_H
#define MAP_GAME_H
#include "../cub3d.h"
#include "../player/player.h"

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
#endif