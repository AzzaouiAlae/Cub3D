#include "player.h"
#include "../map_game/map_game.h"

bool is_teleportation_move(t_point dir)
{
	t_point pos;

	pos.x = dir.x * (TILESIZE + SAFETY * 3);
	pos.y = dir.y * (TILESIZE + SAFETY * 3);
	if (is_valid_move(pos.x, pos.y))
	{
		play_video("media/gate5.mp4");
		g_gate_video = true;
		g_player.pixl_pos.x += pos.x;
		g_player.pixl_pos.y += pos.y;
		return true;
	}
	return false;
}

bool is_open_gate(int x, int y)
{
	return check_pos(g_player.pixl_pos.x + x, g_player.pixl_pos.y + y) == e_opened_gate;
}

