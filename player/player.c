#include "player.h"
#include "../map_game/map_game.h"

;

bool is_valid_move(double x, double y)
{
	t_point pos;

	pos.x = g_player.pixl_pos.x + x;
	pos.y = g_player.pixl_pos.y + y;
	if (check_pos(pos.x, pos.y) != e_empty)
		return false;
	if (check_pos(pos.x + SAFETY, pos.y) != e_empty)
		return false;
	if (check_pos(pos.x , pos.y + SAFETY) != e_empty)
		return false;
	if (check_pos(pos.x - SAFETY, pos.y) != e_empty)
		return false;
	if (check_pos(pos.x , pos.y - SAFETY) != e_empty)
		return false;
	return true;
}

void player_walk(double angle, double speed)
{
	t_point dir;
	int i;

	i = 0;
	normalize_angle(&angle);
	dir.x = cos(angle * M_PI / 180);
	dir.y = -sin(angle * M_PI / 180);
	while(i < speed)
	{
		if (is_open_gate(dir.x * SAFETY * 2, dir.y * SAFETY * 2))
		{
			if (is_teleportation_move(dir))
				break;
		}
		if (is_valid_move(dir.x, 0))
			g_player.pixl_pos.x += dir.x;
		if (is_valid_move(0, dir.y))
			g_player.pixl_pos.y += dir.y;
		i++;
	}
}

void open_close_door()
{
	t_str	**the_map;
	double dist;

	g_keys.o = 2;
	the_map = g_map->content;
	dist = ph_distance((t_point){0,0}, (t_point){TILESIZE * 1.5, TILESIZE * 1.5});
	if (dist < g_door_info.dist)
		return;
	if (the_map[g_door_info.row]->content[g_door_info.col] == 'D')
		the_map[g_door_info.row]->content[g_door_info.col] = 'd';
	else if (the_map[g_door_info.row]->content[g_door_info.col] == 'd')
		the_map[g_door_info.row]->content[g_door_info.col] = 'D';
}

void media_walking()
{
	static int audio_index;
	
	if (audio_index > 2)
		audio_index = 0;
	set_play_speed(100);
	if (audio_index == 0)
		play_audio("media/walking1.mp3");
	else if (audio_index == 1)
		play_audio("media/walking2.mp3");
	else if (audio_index == 2)
		play_audio("media/walking3.mp3");
	audio_index++;
}

void move_player()
{
	g_old_time = g_time;
	g_time = get_curr_time();
	calculate_player_speed();
	if (g_keys.w || g_keys.d || g_keys.a || g_keys.s)
		media_walking();
	if (g_keys.w)
		player_walk(g_player.angle, g_player.move_speed);
	if (g_keys.d)
		player_walk(g_player.angle - 90, g_player.move_speed);
	if (g_keys.a)
		player_walk(g_player.angle + 90, g_player.move_speed);
	if (g_keys.s)
		player_walk(g_player.angle + 180, g_player.move_speed);
	if (g_keys.left)
	{
		g_player.angle += g_player.turn_speed;
		normalize_angle(&g_player.angle);
	}
	if (g_keys.right)
	{
		g_player.angle -= g_player.turn_speed;
		normalize_angle(&g_player.angle);
	}
	if (g_keys.o == 1)
		open_close_door();
}
