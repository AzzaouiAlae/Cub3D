#include "imgs.h"

int g_fps;

int fps(bool set, int fps)
{
    static int value;

    if (set)
        value = fps;
    return value;
}

t_data *get_open_door_img()
{
	static int i;
	static long old_time;

    fps(true, O_FPS);
	return get_wall_img(g_info.list_open_door, g_info.open_door, &i, &old_time);
}

t_data *get_close_door_img()
{
	static int i;
	static long old_time;

	fps(true, C_FPS);
	return get_wall_img(g_info.list_close_door, g_info.close_door, &i, &old_time);
}
