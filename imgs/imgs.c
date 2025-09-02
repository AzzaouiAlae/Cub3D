#include "imgs.h"

t_data *get_east_img()
{
	static int i;
	static long old_time;

	fps(true, E_FPS);
	return get_wall_img(g_info.list_east, g_info.east, &i, &old_time);
}

t_data *get_north_img()
{
	static int i;
	static long old_time;

	fps(true, N_FPS);
	return get_wall_img(g_info.list_north, g_info.north, &i, &old_time);
}

t_data *get_south_img()
{
	static int i;
	static long old_time;

	fps(true, S_FPS);
	return get_wall_img(g_info.list_south, g_info.south, &i, &old_time);
}

t_data *get_west_img()
{
	static int i;
	static long old_time;

	fps(true, W_FPS);
	return get_wall_img(g_info.list_west, g_info.west, &i, &old_time);
}

t_data *get_wall_img(t_list *list, t_data *data, int *i, long *old_time)
{
	t_data **imgs;

	if (list)
		imgs = list->content;
	else
		return data;
	
	if ((1e6 / fps(false, 0)) < (g_time - *old_time))
	{
		(*i)++;
		*old_time = g_time;
	}
	if (*i > list->count - 1)
		*i = 0;
	return imgs[*i];
}
