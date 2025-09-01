#include "imgs.h"


int g_fps;

t_data *get_east_img()
{
	static int i;
	static long old_time;

	g_fps = E_FPS;
	return get_wall_img(g_info.list_east, g_info.east, &i, &old_time);
}

t_data *get_north_img()
{
	static int i;
	static long old_time;

	g_fps = N_FPS;
	return get_wall_img(g_info.list_north, g_info.north, &i, &old_time);
}

t_data *get_south_img()
{
	static int i;
	static long old_time;

	g_fps = S_FPS;
	return get_wall_img(g_info.list_south, g_info.south, &i, &old_time);
}

t_data *get_west_img()
{
	static int i;
	static long old_time;

	g_fps = W_FPS;
	return get_wall_img(g_info.list_west, g_info.west, &i, &old_time);
}

t_data *get_open_door_img()
{
	static int i;
	static long old_time;

	g_fps = O_FPS;
	return get_wall_img(g_info.list_open_door, g_info.open_door, &i, &old_time);
}

t_data *get_close_door_img()
{
	static int i;
	static long old_time;

	g_fps = C_FPS;
	return get_wall_img(g_info.list_close_door, g_info.close_door, &i, &old_time);
}

t_data *get_wall_img(t_list *list, t_data *data, int *i, long *old_time)
{
	t_data **imgs;

	if (list)
		imgs = list->content;
	else
		return data;
	
	if ((1e6 / g_fps) < (g_time - *old_time))
	{
		(*i)++;
		*old_time = g_time;
	}
	if (*i > list->count - 1)
		*i = 0;
	return imgs[*i];
}
